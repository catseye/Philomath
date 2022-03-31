/*
 * Proof that
 *  (p /\ q) -> (q /\ p)
 */

/*
 * suppose (p /\ q) [1]
 * then p, by conj_elim_lhs
 * then q, by conj_elim_rhs
 * then q /\ p, by conj_intro
 * then (p /\ q) -> (q /\ p), by impl_intro [1]
 */

#include "formula.h"
#include "proof.h"

int main(int argc, char **argv) {
    return proves(
        impl_intro(
            1,
            conj_intro(
                conj_elim_rhs(
                    suppose(conj(var("p"), var("q")), 1)
                ),
                conj_elim_lhs(
                    suppose(conj(var("p"), var("q")), 1)
                )
            )
        ),
        impl(conj(var("p"), var("q")), conj(var("q"), var("p")))
    );
}
