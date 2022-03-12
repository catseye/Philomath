Philomath
=========

An LCF-style theorem prover written in ANSI C.

It implements a Natural Deduction system with labelled assumptions.
The rules of inference implement the intuitionistic propositional calculus.

How do I write a proof with this?
---------------------------------

Create a file `eg/myproof.c`:

```c
#include "formula.h"
#include "proof.h"
int main(int argc, char **argv) {
    ...
}
```

Then compile this:

    ./build-proof eg/myproof

And run the resulting executable:

    ./eg/myproof

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

TODO
----

*   Demo proofs
*   Cmd to build and run a demo proof
