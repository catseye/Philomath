/*
 * Proof that
 *  (p -> q) -> ((q -> r) -> (p -> r))
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    return proves(
        impl_intro(
            3,
            impl_intro(
                2,
                impl_intro(
                    1,
                    impl_elim(
                        impl_elim(
                            suppose(var("p"), 1),
                            suppose(impl(var("p"), var("q")), 3)
                        ),
                        suppose(impl(var("q"), var("r")), 2)
                    )
                )
            )
        ),
        impl(impl(var("p"), var("q")), impl(impl(var("q"), var("r")), impl(var("p"), var("r"))))
    );
}
