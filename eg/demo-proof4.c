/*
 * INCOMPLETE Proof that
 *  ~p \/ q -> (p -> q)
 */

/*
 * Suppose ~p \/ q (1)
 * Now, suppose ~p (2)
 * Further, suppose p (3)
 * So bottom, by neg_elim
 * Hence q, by absr_elim
 * Hence, p -> q by (3)
 * Now, suppose q (4)
 * Further, suppose p (5)
 * Hence, p -> q by (5)
 * So, p -> q by disj_elim with (2), (4)
 * So, ~p \/ q -> (p -> q) by (1)
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    struct proof *step1 = suppose(disj(neg(var("p")), var("q")), 1);
    struct proof *step2 = suppose(neg(var("p")), 2);
    struct proof *step3 = suppose(var("p"), 3);
    struct proof *step4 = neg_elim(step3, step2);
    /* ... TODO ... */
    struct proof *step99 = impl_intro(1, step1);

    return proves(
        step99,
        impl(disj(neg(var("p")), var("q")), impl(var("p"), var("q")))
    );
}
