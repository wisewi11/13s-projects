#include "item.h"

#include <stdio.h>
#include <string.h>

// implementation of the cmp() function on items, for when items are ints
bool cmp(item *i1, item *i2) {

    bool joe = strcmp(i1->key, i2->key) == 0;
    return joe;
}
