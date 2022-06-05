/*
 * Proof that
 *  (~p -> _|_) -> p
 * (a.k.a. reductio ad absurdum.  classical logic required.)
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    struct proof *step1 = suppose(impl(neg(var("p")), absr()), 1);    /* Suppose ~p -> _|_ (1) */
    struct proof *step2 = suppose(neg(var("p")), 2);                  /* Now, suppose ~p (2) */
    struct proof *step3 = impl_elim(step2, step1);                    /* Hence, _|_ */
    struct proof *step4 = neg_intro(2, step3);                        /* And thus ~ our ~p, a.k.a. ~~p */
    struct proof *step5 = double_neg_elim(step4);                     /* a.k.a. p, to a classicist */
    struct proof *step6 = impl_intro(1, step5);                       /* So (~p -> _|_) -> p */
    return proves(
        step6,
        impl(impl(neg(var("p")), absr()), var("p"))
    );
}
