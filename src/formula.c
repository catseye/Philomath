#include <stdlib.h>

#include "formula.h"

struct formula *
mk_formula(int type, const char *name, struct formula *lhs, struct formula *rhs) {
    struct formula *f = malloc(sizeof(struct formula));
    f->type = type;
    f->name = name;
    f->lhs = lhs;
    f->rhs = rhs;
    return f;
}

struct formula *
var(const char *name) {
    return mk_formula(VAR, name, NULL, NULL);
}

struct formula *
conj(struct formula *lhs, struct formula *rhs) {
    return mk_formula(CONJ, NULL, lhs, rhs);
}

struct formula *
disj(struct formula *lhs, struct formula *rhs) {
    return mk_formula(DISJ, NULL, lhs, rhs);
}

struct formula *
impl(struct formula *lhs, struct formula *rhs) {
    return mk_formula(IMPL, NULL, lhs, rhs);
}

struct formula *
neg(struct formula *rhs) {
    return mk_formula(NEG, NULL, NULL, rhs);
}

int
formula_eq(struct formula *a, struct formula *b) {
    if (a == NULL && b == NULL) {
        return 1;
    }
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->type != b->type) {
        return 0;
    }
    if (a->type == VAR && !strcmp(a->name, b->name)) {
        return 1;
    }
    if (a->type == CONJ || a->type == DISJ || a->type == IMPL) {
        return formula_eq(a->lhs, b->lhs) && formula_eq(a->rhs, b->rhs);
    }
    if (a->type == NEG) {
        return formula_eq(a->rhs, b->rhs);
    }
    return 0;
}
