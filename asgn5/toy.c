#include "ll.h"

#include <stdio.h>
#include <string.h>

#define MAGICN 457

int main() {
    LL *l = list_create();
    for (int i = 0; i < 1000; i++) {

        item j;
        char k[255];

        sprintf(k, "%d", i);
        strcpy(j.key, k);

        list_add(l, &j);
    }

    item i;
    char key[255];

    sprintf(key, "%d", MAGICN);
    strcpy(i.key, key);

    list_remove(l, cmp, &i);

    item *ret;

    for (int i = 0; i < 1000; i++) {

        item j;
        char k[255];

        sprintf(k, "%d", i);
        strcpy(j.key, k);

        if (i != MAGICN) {
            ret = list_find(l, cmp, &j);
            if (ret == NULL) {
                printf("something went wrong. I inserted %d into the list but then could not find "
                       "it.\n",
                    i);
                return 1;
            }
        } else {

            ret = list_find(l, cmp, &j);
            if (ret == NULL) {
                continue;
            }
            printf("somethign went wrong. MAGICN should be removed from list.\n");
        }
    }
    list_destroy(&l);

    l = list_create();

    list_add(l, &i);
    list_remove(l, cmp, &i);

    ret = list_find(l, cmp, &i);
    if (ret) {
        printf("something went wrong. MAGICN should be removed from list.\n");
    }

    list_destroy(&l);

    return 0;
}
