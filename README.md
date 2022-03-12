Philomath
=========

An LCF-style theorem prover written in ANSI C.  It implements a
Natural Deduction system with labelled assumptions.  For more information
on this approach, see [LCF-Style-ND](https://github.com/catseye/LCF-Style-ND).
The supplied rules of inference implement the intuitionistic propositional calculus.

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

Progress
--------

- [x] conj_intro
- [x] conj_elim
- [x] impl_intro
- [x] impl_elim
- [x] disj_intro
- [x] disj_elim
- [ ] abs_elim: if abs is proved, then anything is proved
- [ ] neg_elim: if x is proved, and not x is proved, then absurdum is proved
- [ ] neg_intro: if gamma, phi proves absurdum, then gamma proves not phi
- [ ] assert

