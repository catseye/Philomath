Philomath
=========

Version 1.1 | _See also:_ [LCF-style-Natural-Deduction][]
∘ [Maxixe](https://codeberg.org/catseye/Maxixe#maxixe)
∘ [Cardboard Prolog](https://codeberg.org/catseye/Cardboard-Prolog#cardboard-prolog)

- - - -

**Philomath** is an LCF-style theorem prover written in ANSI C.  It implements
[classical propositional logic][] inside a [Natural Deduction][] system with
labelled assumptions.  For more information on this approach, see the
**[LCF-style-Natural-Deduction][]** article.

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

If you wish to build the proof with debugging output, you can pass the `-D` flag:

    ./build-proof.sh -D myproof

Limitations
-----------

LCF-style theorem proving relies on data abstraction, i.e. information hiding.
In C, information hiding is accomplished by exposing, in a header file, only the
fact that a `struct` exists, and *not* exposing its structure.  Client code can then
work with pointers to that `struct` without knowing what's contained in it.

It is however possible to subvert this mechanism.  If your proof code does any of
the following things, it is possible it is no longer a valid proof:

*   includes the file `proof.c` directly, rather than including `proof.h`
*   casts a `struct theorem` value to some other type
*   casts a value of some other type to a `struct theorem`

Fortunately, it is possible to statically analyze a C source file and confirm
that it does none of these things, if such a level of assurance is desired.

TODO
----

Should really have even more demo non-proofs, to help ensure that it's not
letting non-proofs pass themselves off as proofs somewhere.

History
-------

### 1.1

*   When creating a `struct theorem` or `struct assumptions`, the
    supplied `struct formula *` is now cloned (deep-copied) before being
    stored in the structure.  This prevents the theorem from being
    manipulated after its creation by updating the contents of the
    `struct formula *` that was used to create it.  Thanks to
    [Proloy Mishra](https://github.com/pro465) for pointing out this
    hole.
*   More test cases, and a driver script (`test.sh`) to run the tests.
*   Added this "History" section to the README.

### 1.0-2022.0905

*   Renamed `struct theorem` to `struct proof`, and `proof.{c,h}` to
    `theorem.{c,h}` to better reflect what these objects are.

### 1.0

*   Initial release of Philomath.

[classical propositional logic]: https://iep.utm.edu/natural-deduction/#H4
[Natural Deduction]: https://iep.utm.edu/natural-deduction/
[LCF-style-Natural-Deduction]: https://codeberg.org/catseye/The-Dossier/src/branch/master/article/LCF-style-Natural-Deduction/
