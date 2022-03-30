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
    assert(p != NULL);
    p->assumptions = assumptions;
    p->conclusion = conclusion;
    return p;
}

int proves(struct proof *p, struct formula *c) {
    /* Asserts that the proof p proves the formula c.  If it does,
       a successful system exit code (i.e. 0) is returned, with
       which the process may exit. */
    assert(p->assumptions == NULL);
    assert(formula_eq(p->conclusion, c));
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
conj_intro(struct proof *p, struct proof *q) {
    /* If p is proved, and q is proved, then p & q is proved. */
    return mk_proof(
        merge(p->assumptions, q->assumptions),
        conj(p->conclusion, q->conclusion)
    );
}

struct proof *
conj_elim_lhs(struct proof *r) {
    /* If r (of the form p & q) is proved, then p is proved. */
    assert(r->conclusion->type == CONJ);
    return mk_proof(
        r->assumptions,
        r->conclusion->lhs
    );
}

struct proof *
conj_elim_rhs(struct proof *r) {
    /* If r (of the form p & q) is proved, then q is proved. */
    assert(r->conclusion->type == CONJ);
    return mk_proof(
        r->assumptions,
        r->conclusion->rhs
    );
}

struct proof *
impl_intro(int label, struct proof *q) {
    /* If q is proved under the assumption p, then p -> q is proved. */
    struct formula *f = lookup(label, q->assumptions);
    struct assumptions *a = discharge(label, q->assumptions);
    return mk_proof(
        a,
        impl(f, q->conclusion)
    );
}

struct proof *
impl_elim(struct proof *p, struct proof *r) {
    /* If p is proved, and r (of the form p -> q) is proved, then q is proved. */
    assert(r->conclusion->type == IMPL);
    assert(formula_eq(r->conclusion->lhs, p->conclusion));
    return mk_proof(
        merge(p->assumptions, r->assumptions),
        r->conclusion->rhs
    );
}

struct proof *
disj_intro_lhs(struct formula *p, struct proof *q) {
    /* If q is proved, then p v q is proved, for any p. */
    return mk_proof(
        q->assumptions,
        disj(p, q->conclusion)
    );
}

struct proof *
disj_intro_rhs(struct proof *p, struct formula *q) {
    /* If p is proved, then p v q is proved, for any q. */
    return mk_proof(
        p->assumptions,
        disj(p->conclusion, q)
    );
}

struct proof *
disj_elim(struct proof *r, struct proof *s, int label1, struct proof *t, int label2) {
    /* If r is proved, and under the assumption labelled "1" s is proved, and under
       the assumption labelled "2" t is proved, and s concludes the same as t,
       and r is proved and r is in the form "1" v "2", then s is proved. */
    struct formula *f1, *f2;
    struct assumptions *a_s, *a_t;

    assert(r->conclusion->type == DISJ);

    f1 = lookup(label1, s->assumptions);
    a_s = discharge(label2, s->assumptions);

    f2 = lookup(label2, t->assumptions);
    a_t = discharge(label2, t->assumptions);

    assert(formula_eq(s->conclusion, t->conclusion));
    assert(formula_eq(r->conclusion->lhs, f1));
    assert(formula_eq(r->conclusion->rhs, f2));

    return mk_proof(
        merge(r->assumptions, merge(a_s, a_t)),
        s->conclusion
    );
}
