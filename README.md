Philomath
=========

**Philomath** is an LCF-style theorem prover written in ANSI C.  It implements
[intuitionistic propositional logic] inside a [Natural Deduction] system with
labelled assumptions.  For more information on this approach, see the
**[LCF-style-ND](https://github.com/cpressey/LCF-style-ND)** repository.

How do I write a proof with this?
---------------------------------

Create a file `myproof.c`:

```c
#include "formula.h"
#include "proof.h"
int main(int argc, char **argv) {
    /* Proof of p -> p */
    return proves(
        impl_intro(1, suppose(var("p"), 1)),
        impl(var("p"), var("p"))
    );
}
```

Then compile and run it with:

    ./build-proof.sh myproof

And run the resulting executable:

    ./myproof.exe

If the exit code is 0, the proof is valid!

    % echo $?
    0

Limitations
-----------

LCF-style theorem proving relies on data abstraction, i.e. information hiding.
In C, information hiding is accomplished by exposing, in a header file, only the
fact that a `struct` exists, and *not* exposing its structure.  Client code can then
work with pointers to that `struct` without knowing what's contained in it.

It is however possible to subvert this mechanism.  If your proof code does any of
the following things, it is possible it is no longer a valid proof:

*   includes the file `proof.c` directly, rather than including `proof.h`
*   casts a `struct proof` value to some other type
*   casts a value of some other type to a `struct proof`

Fortunately, it is possible to statically analyze a C source file and confirm
that it does none of these things, if such a level of assurance is desired.

Progress
--------

- [x] assert()
- [x] proves()

- [x] impl_intro
- [x] demo proof showing impl_intro
- [x] impl_elim
- [x] demo proof showing impl_elim

- [x] conj_intro
- [x] demo proof showing conj_intro
- [x] conj_elim
- [x] demo proof showing conj_elim

- [x] disj_intro
- [x] demo proof showing disj_intro
- [x] disj_elim
- [x] demo proof showing disj_elim

- [ ] demo bad proof (ought to really be a number of these)
- [ ] debug flag for (or debug version of) `build-proof.sh`

- [ ] Use names of greek letters for arguments to the functions

- [ ] Absurdum value
- [ ] abs_elim: if abs is proved, then anything is proved (abs |- phi)
- [ ] demo proof showing abs_elim
- [ ] neg_elim: if x is proved, and not x is proved, then absurdum is proved (phi, not phi |- abs)
- [ ] demo proof showing neg_elim
- [ ] neg_intro: if gamma, phi proves absurdum, then gamma proves not phi (gamma |- not phi, discharging gamma, phi)
- [ ] demo proof showing neg_intro

[intuitionistic propositional logic]: https://iep.utm.edu/natural-deduction/#H4
[Natural Deduction]: https://iep.utm.edu/natural-deduction/
