#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "formula.h"
#include "assumptions.h"
#include "proof.h"

struct proof {
    struct assumptions *assumptions;
    struct formula *conclusion;
};

struct proof *
mk_proof(struct assumptions *assumptions, struct formula *conclusion) {
    struct proof *p = (struct proof *)malloc(sizeof(struct proof));
    assert(p != NULL, "mk_proof: could not allocate proof object");
#ifdef DEBUG
    fprintf(stdout, "-----------------------------------------\n");
    fprintf(stdout, "Created proof of ");
    formula_fprint(stdout, conclusion);
    fprintf(stdout, " under assumptions:\n");
    assumptions_fprint(stdout, assumptions);
    fprintf(stdout, "-----------------------------------------\n\n");
#endif
    p->assumptions = assumptions;
    p->conclusion = conclusion;
    return p;
}

int proves(struct proof *p, struct formula *c) {
    /* Asserts that the proof p proves the formula c.  If it does,
       a successful system exit code (i.e. 0) is returned, with
       which the process may exit. */
    assert(p->assumptions == NULL, "proves: proof contains undischarged assumptions");
#ifdef DEBUG
    if (!formula_eq(p->conclusion, c)) {
        fprintf(stdout, "Claim:               ");
        formula_fprint(stdout, c);
        fprintf(stdout, "\n");
        fprintf(stdout, "Conclusion of proof: ");
        formula_fprint(stdout, p->conclusion);
        fprintf(stdout, "\n");
    }
#endif
    assert(formula_eq(p->conclusion, c), "proves: proof does not prove what is claimed");
    return 0;
}

struct proof *
suppose(struct formula *formula, int label) {
    return mk_proof(
        assume(label, formula, NULL),
        formula
    );
}

struct proof *
conj_intro(struct proof *x, struct proof *y) {
    /* If x is proved, and y is proved, then x & y is proved. */
    return mk_proof(
        merge(x->assumptions, y->assumptions),
        conj(x->conclusion, y->conclusion)
    );
}

struct proof *
conj_elim_lhs(struct proof *x) {
    /* If x (of the form y & z) is proved, then y is proved. */
    assert(x->conclusion->type == CONJ, "conj_elim_lhs: not a conjunction");
    return mk_proof(
        x->assumptions,
        x->conclusion->lhs
    );
}

struct proof *
conj_elim_rhs(struct proof *x) {
    /* If x (of the form y & z) is proved, then z is proved. */
    assert(x->conclusion->type == CONJ, "conj_elim_rhs: not a conjunction");
    return mk_proof(
        x->assumptions,
        x->conclusion->rhs
    );
}

struct proof *
impl_intro(int label, struct proof *y) {
    /* If y is proved under the assumption x, then x -> y is proved. */
    struct formula *f = lookup(label, y->assumptions);
    struct assumptions *a = discharge(label, y->assumptions);
#ifdef DEBUG
    if (f == NULL) {
        fprintf(stdout, "Label %d not found in:", label);
        assumptions_fprint(stdout, a);
        fprintf(stdout, "\n");
    }
#endif
    assert(f != NULL, "impl_intro: label not found in assumptions");
    return mk_proof(
        a,
        impl(f, y->conclusion)
    );
}

struct proof *
impl_elim(struct proof *x, struct proof *y) {
    /* If x is proved, and y (of the form x -> z) is proved, then z is proved. */
    assert(y->conclusion->type == IMPL, "impl_elim: not an implication");
    assert(formula_eq(y->conclusion->lhs, x->conclusion), "impl_elim: formula mismatch");
    return mk_proof(
        merge(x->assumptions, y->assumptions),
        y->conclusion->rhs
    );
}

struct proof *
disj_intro_lhs(struct formula *fx, struct proof *y) {
    /* If y is proved, then x v y is proved, for any x. */
    return mk_proof(
        y->assumptions,
        disj(fx, y->conclusion)
    );
}

struct proof *
disj_intro_rhs(struct proof *x, struct formula *fy) {
    /* If x is proved, then x v y is proved, for any y. */
    return mk_proof(
        x->assumptions,
        disj(x->conclusion, fy)
    );
}

struct proof *
disj_elim(struct proof *z, struct proof *x, int label1, struct proof *y, int label2) {
    /* If z is proved, and under the assumption labelled "1" x is proved, and under
       the assumption labelled "2" y is proved, and x concludes the same as y,
       and z is proved and z is in the form "1" v "2", then x is proved. */
    struct formula *f1, *f2;
    struct assumptions *a_x, *a_y;

    assert(z->conclusion->type == DISJ, "disj_elim: not a disjunction");

    f1 = lookup(label1, x->assumptions);
    a_x = discharge(label1, x->assumptions);

    f2 = lookup(label2, y->assumptions);
    a_y = discharge(label2, y->assumptions);

    assert(formula_eq(x->conclusion, y->conclusion), "disj_elim: mismatched conclusions");
    assert(formula_eq(z->conclusion->lhs, f1), "disj_elim: mismatched assumption on lhs");
    assert(formula_eq(z->conclusion->rhs, f2), "disj_elim: mismatched assumption on rhs");

    return mk_proof(
        merge(z->assumptions, merge(a_x, a_y)),
        x->conclusion
    );
}

struct proof *
neg_intro(int label, struct proof *x)
{
    /* If x is absurdum and x is proved under the assumption y, then not-y is proved. */
    struct formula *f = lookup(label, x->assumptions);
    struct assumptions *a = discharge(label, x->assumptions);
    assert(x->conclusion->type == ABSR, "neg_intro: not absurdum");
#ifdef DEBUG
    if (f == NULL) {
        fprintf(stdout, "Label %d not found in:", label);
        assumptions_fprint(stdout, a);
        fprintf(stdout, "\n");
    }
#endif
    assert(f != NULL, "neg_intro: label not found in assumptions");
    return mk_proof(
        a,
        neg(f)
    );
}

struct proof *
neg_elim(struct proof *x, struct proof *y)
{
    /* If x has the form z and x is proved, and y has the form not-z and y is proved,
       then absurdum is proved. */
    assert(y->conclusion->type == NEG, "neg_elim: not a negation");
    assert(formula_eq(x->conclusion, y->conclusion->rhs), "neg_elim: mismatched conclusions");
    return mk_proof(
        merge(x->assumptions, y->assumptions),
        absr()
    );
}

struct proof *
absr_elim(struct proof *x, struct formula *fy)
{
    /* If x is absurdum and x is proved, then y is proved for any y. */
    assert(x->conclusion->type == ABSR, "absr_elim: not absurdum");
    return mk_proof(
        x->assumptions,
        fy
    );
}

struct proof *
double_neg_elim(struct proof *x)
{
    assert(x->conclusion->type == NEG, "double_neg_elim: not a negation");
    assert(x->conclusion->rhs->type == NEG, "double_neg_elim: not a double negation");
    return mk_proof(
        x->assumptions,
        x->conclusion->rhs->rhs
    );
}
