
#include "badhash.h"
size_t hash(char *key) {
    // THIS IS NOT A GOOD HASH FUNCTION!!
    //
    size_t x = 0;
    for (size_t i = 0; i < 3 && i < strlen(key); i++) {
        size_t c = (size_t) key[i];
        x |= (c << (8 * i));
    }
    return x;
}
