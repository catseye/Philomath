/* formula.h */

#ifndef FORMULA_H
#define FORMULA_H 1

#include <stdio.h>  /* for definition of FILE only */

#define VAR  0
#define CONJ 1
#define DISJ 2
#define IMPL 3
#define NEG  4
#define ABSR 5

struct formula {
    int type;
    const char *name;
    struct formula *lhs;  /* will be NULL for NEG, ABSR */
    struct formula *rhs;  /* will be NULL for ABSR */
};

struct formula *var(const char *);
struct formula *conj(struct formula *, struct formula *);
struct formula *disj(struct formula *, struct formula *);
struct formula *impl(struct formula *, struct formula *);
struct formula *neg(struct formula *);
struct formula *absr(void);

int formula_eq(struct formula *, struct formula *);
struct formula *formula_clone(struct formula *);
void formula_fprint(FILE *, struct formula *);

#endif /* ndef FORMULA_H */
