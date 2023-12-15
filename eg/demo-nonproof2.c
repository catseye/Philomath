/*
 * Attempt to write a proof showing
 *  (q -> q) -> ((q -> r) -> (p -> r))
 * but demonstrate that we do not allow that.
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
                            suppose(impl(var("q"), var("q")), 3)
                        ),
                        suppose(impl(var("q"), var("r")), 2)
                    )
                )
            )
        ),
        impl(impl(var("q"), var("q")), impl(impl(var("q"), var("r")), impl(var("p"), var("r"))))
    );
}
