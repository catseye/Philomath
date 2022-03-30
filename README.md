philomath
=========

**philomath** is an LCF-style theorem prover written in ANSI C.  It implements
intuitionistic propositional logic inside a Natural Deduction system with
labelled assumptions.  For more information on this approach, see
[LCF-Style-ND](https://github.com/catseye/LCF-Style-ND).

How do I write a proof with this?
---------------------------------

Create a file `myproof.c`:

```c
#include "formula.h"
#include "proof.h"
int main(int argc, char **argv) {
    ...
}
```

Then compile and run it with:

    ./build-proof.sh myproof

And run the resulting executable:

    ./myproof

If the exit code is 0, the proof is valid!

    % echo $?
    0

Limitations
-----------

LCF-style theorem proving relies on data abstraction, that is, information hiding.
In C, information hiding is accomplished by exposing, in a header file, only the
fact that a struct exists, and *not* exposing its structure.  Client code can then
work with

It is however possible to subvert this mechanism.  If your proof code does any of#
the following things, it is possible it is no longer a valid proof:

*   includes `proof.c` rather than `proof.h`
*   casts a `struct proof` value to some other type

Progress
--------

- [x] assert()
- [ ] proves()

- [x] impl_intro
- [x] demo proof showing impl_intro
- [x] impl_elim
- [x] demo proof showing impl_elim

- [x] conj_intro
- [ ] demo proof showing conj_intro
- [x] conj_elim
- [ ] demo proof showing conj_elim

- [x] disj_intro
- [ ] demo proof showing disj_intro
- [x] disj_elim
- [ ] demo proof showing disj_elim

- [ ] Absurdum value
- [ ] abs_elim: if abs is proved, then anything is proved
- [ ] demo proof showing abs_elim
- [ ] neg_elim: if x is proved, and not x is proved, then absurdum is proved
- [ ] demo proof showing neg_elim
- [ ] neg_intro: if gamma, phi proves absurdum, then gamma proves not phi
- [ ] demo proof showing neg_intro
