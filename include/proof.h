/* proof.h */

#ifndef PROOF_H
#define PROOF_H 1

#include "formula.h"

struct proof;

int proves(struct proof *, struct formula *);

struct proof *suppose(struct formula *, int);

struct proof *conj_intro(struct proof *, struct proof *);
struct proof *conj_elim_lhs(struct proof *);
struct proof *conj_elim_rhs(struct proof *);

struct proof *impl_intro(int, struct proof *);
struct proof *impl_elim(struct proof *, struct proof *);

struct proof *disj_intro_lhs(struct formula *, struct proof *);
struct proof *disj_intro_rhs(struct proof *, struct formula *);
struct proof *disj_elim(struct proof *, struct proof *, int, struct proof *, int);

struct proof *conj_elim_lhs(struct proof *);
struct proof *conj_elim_rhs(struct proof *);

struct proof *neg_intro(int, struct proof *);
struct proof *neg_elim(struct proof *, struct proof *);

struct proof *absr_elim(struct proof *, struct formula *);

#endif /* ndef PROOF_H */
