/*
 * Proof that
 *  p \/ q -> q \/ p
 */

/*
 * Suppose p \/ q (1)
 * Then, suppose p (2)
 * Then, q \/ p by disj intro
 * And then, suppose q (3)
 * Then, q \/ p by disj intro
 * So, q \/ p by disj elim
 * So, p \/ q -> q \/ p by 1
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    return proves(
        impl_intro(
            1,
            disj_elim(
                suppose(disj(var("p"), var("q")), 1),
                disj_intro_lhs(var("q"), suppose(var("p"), 2)), 2,
                disj_intro_rhs(suppose(var("q"), 3), var("p")), 3
            )
        ),
        impl(disj(var("p"), var("q")), disj(var("q"), var("p")))
    );
}
