#ifndef _HASH

#define _HASH

#define HASH_BUCKET_SIZE 1500

#include "ll.h"

typedef struct Hashtable Hashtable;

struct Hashtable {
    LL *ll[HASH_BUCKET_SIZE];
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
