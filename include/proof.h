/* proof.h */

#ifndef PROOF_H
#define PROOF_H 1

#include "formula.h"

struct theorem;

int proves(struct theorem *, struct formula *);

struct theorem *suppose(struct formula *, int);

struct theorem *conj_intro(struct theorem *, struct theorem *);
struct theorem *conj_elim_lhs(struct theorem *);
struct theorem *conj_elim_rhs(struct theorem *);

struct theorem *impl_intro(int, struct theorem *);
struct theorem *impl_elim(struct theorem *, struct theorem *);

struct theorem *disj_intro_lhs(struct formula *, struct theorem *);
struct theorem *disj_intro_rhs(struct theorem *, struct formula *);
struct theorem *disj_elim(struct theorem *, struct theorem *, int, struct theorem *, int);

struct theorem *conj_elim_lhs(struct theorem *);
struct theorem *conj_elim_rhs(struct theorem *);

struct theorem *neg_intro(int, struct theorem *);
struct theorem *neg_elim(struct theorem *, struct theorem *);

struct theorem *absr_elim(struct theorem *, struct formula *);
struct theorem *double_neg_elim(struct theorem *);

#endif /* ndef PROOF_H */
