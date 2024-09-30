#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *abstractwords(int iters, void *ds, void (*dsdo)(void *, char *, int)) {
    ssize_t readLine;
    char *line = NULL;
    size_t size = 0;
    int i = 0;

    for (int times = 0; times < iters; times++) {
        FILE *fp = fopen("/usr/share/dict/words", "r");
        if (fp == NULL) {
            perror("no dictionary file\n");
            return NULL;
        }
        while ((readLine = getline(&line, &size, fp)) != -1) {
            line[readLine - 1] = '\0';
            dsdo(ds, line, i);
            i++;
        }
        fclose(fp);
    }

    free(line);
    return ds;
}
