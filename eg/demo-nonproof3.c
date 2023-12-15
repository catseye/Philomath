/*
 * Attempt to manipulate a proof, after constructing it,
 * by changing the formula it proves.
 * But demonstrate that we do not allow that.
 * (If all calls to formula_clone() are removed from theorem.c
 * and assumptions.c, this "proof" will incorrectly succeed.)
 */

#include "formula.h"
#include "assumptions.h"
#include "proof.h"

int main(int argc, char **argv) {
    /* "Proof" that (q -> q) -> ((q -> r) -> (p -> r)) */
    struct formula *f1 = impl(var("p"), var("q"));
    struct formula *f2 = impl(var("q"), var("r"));
    struct theorem *th = impl_elim(
        impl_elim(
            suppose(var("p"), 1),
            suppose(f1, 3)
        ),
        suppose(f2, 2)
    );
    f1->lhs = var("q");  /* BWAAAA HA HA HA HA */
    return proves(
        impl_intro(
            3,
            impl_intro(
                2,
                impl_intro(
                    1,
                    th
                )
            )
        ),
        impl(impl(var("q"), var("q")), impl(impl(var("q"), var("r")), impl(var("p"), var("r"))))
    );
}
