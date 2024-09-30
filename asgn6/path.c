#include "path.h"

#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;

    p->vertices = stack_create(capacity);

    return p;
}

void path_free(Path **pp) {
    if (pp != NULL) {
        if (*pp != NULL) {

            Stack *temp_stack = (*pp)->vertices;
            stack_free(&temp_stack);
            free(*pp);
        }
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_empty(p->vertices) == false) {
        uint32_t prev_val = 9999999;
        stack_peek(p->vertices, &prev_val);
        uint32_t w = graph_get_weight(g, prev_val, val);
        p->total_weight += w;
    }

    stack_push(p->vertices, val);
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex = 9999999;
    stack_pop(p->vertices, &removed_vertex);

    if (!stack_empty(p->vertices)) {
        uint32_t prev_vertex = 9999999;
        stack_peek(p->vertices, &prev_vertex);
        uint32_t w = graph_get_weight(g, prev_vertex, removed_vertex);
        p->total_weight -= w;
    } else {
        p->total_weight = 0;
    }

    return removed_vertex;
}

void path_copy(Path *dst, const Path *src) {

    stack_copy(dst->vertices, src->vertices);

    dst->total_weight = src->total_weight;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    assert(f != NULL);
    stack_print(p->vertices, f, graph_get_names(g));
}
