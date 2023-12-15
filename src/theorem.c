#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "formula.h"
#include "assumptions.h"
#include "proof.h"

struct theorem {
    struct assumptions *assumptions;
    struct formula *conclusion;
};

struct theorem *
mk_theorem(struct assumptions *assumptions, struct formula *conclusion) {
    struct theorem *t = (struct theorem *)malloc(sizeof(struct theorem));
    assert(t != NULL, "mk_theorem: could not allocate theorem object");
#ifdef DEBUG
    fprintf(stdout, "-----------------------------------------\n");
    fprintf(stdout, "Created theorem ");
    formula_fprint(stdout, conclusion);
    fprintf(stdout, " under assumptions:\n");
    assumptions_fprint(stdout, assumptions);
    fprintf(stdout, "-----------------------------------------\n\n");
#endif
    t->assumptions = assumptions;
    t->conclusion = formula_clone(conclusion);
    return t;
}

int proves(struct theorem *t, struct formula *c) {
    /* Asserts that the theorem t proves the formula c.  If it does,
       a successful system exit code (i.e. 0) is returned, with
       which the process may exit. */
    assert(t->assumptions == NULL, "proves: proof contains undischarged assumptions");
#ifdef DEBUG
    if (!formula_eq(t->conclusion, c)) {
        fprintf(stdout, "Claim:               ");
        formula_fprint(stdout, c);
        fprintf(stdout, "\n");
        fprintf(stdout, "Conclusion of proof: ");
        formula_fprint(stdout, t->conclusion);
        fprintf(stdout, "\n");
    }
#endif
    assert(formula_eq(t->conclusion, c), "proves: proof does not prove what is claimed");
    return 0;
}

struct theorem *
suppose(struct formula *formula, int label) {
    return mk_theorem(
        assume(label, formula, NULL),
        formula
    );
}

struct theorem *
conj_intro(struct theorem *x, struct theorem *y) {
    /* If x is a theorem, and y is a theorem, then x & y is a theorem. */
    return mk_theorem(
        merge(x->assumptions, y->assumptions),
        conj(x->conclusion, y->conclusion)
    );
}

struct theorem *
conj_elim_lhs(struct theorem *x) {
    /* If x (of the form y & z) is a theorem, then y is a theorem. */
    assert(x->conclusion->type == CONJ, "conj_elim_lhs: not a conjunction");
    return mk_theorem(
        x->assumptions,
        x->conclusion->lhs
    );
}

struct theorem *
conj_elim_rhs(struct theorem *x) {
    /* If x (of the form y & z) is a theorem, then z is a theorem. */
    assert(x->conclusion->type == CONJ, "conj_elim_rhs: not a conjunction");
    return mk_theorem(
        x->assumptions,
        x->conclusion->rhs
    );
}

struct theorem *
impl_intro(int label, struct theorem *y) {
    /* If y is a theorem under the assumption x, then x -> y is a theorem. */
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
    return mk_theorem(
        a,
        impl(f, y->conclusion)
    );
}

struct theorem *
impl_elim(struct theorem *x, struct theorem *y) {
    /* If x is a theorem, and y (of the form x -> z) is a theorem, then z is a theorem. */
    assert(y->conclusion->type == IMPL, "impl_elim: not an implication");
    assert(formula_eq(y->conclusion->lhs, x->conclusion), "impl_elim: formula mismatch");
    return mk_theorem(
        merge(x->assumptions, y->assumptions),
        y->conclusion->rhs
    );
}

struct theorem *
disj_intro_lhs(struct formula *fx, struct theorem *y) {
    /* If y is a theorem, then x v y is a theorem, for any x. */
    return mk_theorem(
        y->assumptions,
        disj(fx, y->conclusion)
    );
}

struct theorem *
disj_intro_rhs(struct theorem *x, struct formula *fy) {
    /* If x is a theorem, then x v y is a theorem, for any y. */
    return mk_theorem(
        x->assumptions,
        disj(x->conclusion, fy)
    );
}

struct theorem *
disj_elim(struct theorem *z, struct theorem *x, int label1, struct theorem *y, int label2) {
    /* If z is a theorem, and under the assumption labelled "1" x is a theorem, and under
       the assumption labelled "2" y is a theorem, and x concludes the same as y,
       and z (in the form "1" v "2") is a theorem, then x is a theorem. */
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

    return mk_theorem(
        merge(z->assumptions, merge(a_x, a_y)),
        x->conclusion
    );
}

struct theorem *
neg_intro(int label, struct theorem *x)
{
    /* If x is absurdum and x is a theorem under the assumption y, then not-y is a theorem. */
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
    return mk_theorem(
        a,
        neg(f)
    );
}

struct theorem *
neg_elim(struct theorem *x, struct theorem *y)
{
    /* If x has the form z and x is a theorem, and y has the form not-z and y is a theorem,
       then absurdum is a theorem. */
    assert(y->conclusion->type == NEG, "neg_elim: not a negation");
    assert(formula_eq(x->conclusion, y->conclusion->rhs), "neg_elim: mismatched conclusions");
    return mk_theorem(
        merge(x->assumptions, y->assumptions),
        absr()
    );
}

struct theorem *
absr_elim(struct theorem *x, struct formula *fy)
{
    /* If x is absurdum and x is a theorem, then y is a theorem for any y. */
    assert(x->conclusion->type == ABSR, "absr_elim: not absurdum");
    return mk_theorem(
        x->assumptions,
        fy
    );
}

struct theorem *
double_neg_elim(struct theorem *x)
{
    /* If x is a theorem and x is in the form not-not-y, then y is a theorem. */
    assert(x->conclusion->type == NEG, "double_neg_elim: not a negation");
    assert(x->conclusion->rhs->type == NEG, "double_neg_elim: not a double negation");
    return mk_theorem(
        x->assumptions,
        x->conclusion->rhs->rhs
    );
}
