/*
 * Proof that
 *  ~p \/ q -> (p -> q)
 *
 * Note that step9 and stepA together simulate a "copy" or
 * "reiteration", where we "import" a proof step (in this
 * case, q) into an assumption we made elsewhere (in this
 * case, p).
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    struct theorem *step1 = suppose(disj(neg(var("p")), var("q")), 1); /* Suppose ~p \/ q (1) */
    struct theorem *step2 = suppose(neg(var("p")), 2);                 /* Now, suppose ~p (2) */
    struct theorem *step3 = suppose(var("p"), 3);                      /* Further, suppose p (3) */
    struct theorem *step4 = neg_elim(step3, step2);                    /* So bottom, by neg_elim */
    struct theorem *step5 = absr_elim(step4, var("q"));                /* Hence q, by absr_elim */
    struct theorem *step6 = impl_intro(3, step5);                      /* Hence, p -> q by (3) */
    struct theorem *step7 = suppose(var("q"), 4);                      /* Now, suppose q (4) */
    struct theorem *step8 = suppose(var("p"), 5);                      /* Further, suppose p (5) */
    struct theorem *step9 = conj_intro(step7, step8);                  /* So q /\ p, by conj_intro */
    struct theorem *stepA = conj_elim_lhs(step9);                      /* So q (under (5)), by conj_elim */
    struct theorem *stepB = impl_intro(5, stepA);                      /* Hence, p -> q by (5) */
    struct theorem *stepC = disj_elim(step1, step6, 2, stepB, 4);      /* So, p -> q by disj_elim with (2), (4) */
    struct theorem *stepD = impl_intro(1, stepC);                      /* So, ~p \/ q -> (p -> q) by (1) */
    return proves(
        stepD,
        impl(disj(neg(var("p")), var("q")), impl(var("p"), var("q")))
    );
}
