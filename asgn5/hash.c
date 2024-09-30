

#include "hash.h"

#include "badhash.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hashtable *hash_create(void) {
    Hashtable *h = (Hashtable *) malloc(sizeof(Hashtable));
    if (h == NULL) {
        return NULL;
    }

    for (int i = 0; i < HASH_BUCKET_SIZE; i++) {
        h->ll[i] = list_create();
    }

    return h;
}

bool hash_put(Hashtable *h, char *key, int val) {

    item i;
    i.id = val;
    strcpy(i.key, key);

    size_t hash_index_num = hash(key);
    int index = hash_index_num % HASH_BUCKET_SIZE;

    LL *l = h->ll[index];
    if (l) {

        item *space = list_find(l, cmp, &i);
        if (space) {
            space->id = val;
        } else {
            list_add(l, &i);
        }

        return true;
    } else {
        return false;
    }
}

int *hash_get(Hashtable *h, char *key) {
    item i;
    strcpy(i.key, key);

    size_t hash_index_num = hash(key);
    int index = hash_index_num % HASH_BUCKET_SIZE;
    LL *l = h->ll[index];
    if (l) {
        item *space = list_find(l, cmp, &i);
        if (space) {
            return &(space->id);
        }
    }

    return NULL;
}

void hash_destroy(Hashtable **h) {
    if (*h) {
        for (int i = 0; i < HASH_BUCKET_SIZE; i++) {
            if ((*h)->ll[i]) {
                list_destroy(&((*h)->ll[i]));
            } else {
                continue;
            }
        }

        free(*h);
        *h = NULL;
    }
}
