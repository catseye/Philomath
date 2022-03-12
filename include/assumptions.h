/* assumptions.h */

#ifndef ASSUMPTIONS_H
#define ASSUMPTIONS_H 1

#include "formula.h"

struct assumptions {
    int label;
    struct formula *formula;
    struct assumptions *next;
};

struct assumptions *assume(int, struct formula *, struct assumptions *);
struct formula *lookup(int, struct assumptions *);
struct assumptions *discharge(int, struct assumptions *);
struct assumptions *merge(struct assumptions *, struct assumptions *);

#endif /* ndef ASSUMPTIONS_H */
