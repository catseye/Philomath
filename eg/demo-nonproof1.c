/*
 * Attempt to write a proof showing
 *  (p -> q) -> p
 * but demonstrate that we do not allow that.
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    return proves(
        impl_intro(
            1,
            suppose(conj(var("p"), var("q")), 1)
        ),
        impl(impl(var("p"), var("q")), var("p"))
    );
}
