#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;

    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));

    g->weights = calloc(vertices, sizeof(g->weights[0]));

    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

void graph_free(Graph **gp) {
    Graph *g = *gp;
    if (gp != NULL && *gp != NULL) {
        for (uint32_t i = 0; i < g->vertices; ++i) {
            free(g->weights[i]);
        }
        for (uint32_t i = 0; i < g->vertices; ++i) {
            free(g->names[i]);
        }

        free(g->weights);
        free(g->names);
        free(g->visited);
        free(g);
    }

    if (gp != NULL) {
        *gp = NULL;
    }
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (start < g->vertices && end < g->vertices) {
        g->weights[start][end] = weight;

        if (g->directed == false) {
            g->weights[end][start] = weight;
        }
    }
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    return g->weights[start][end];
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    if (v < g->vertices) {
        g->visited[v] = true;
    }
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    if (v < g->vertices) {
        g->visited[v] = false;
    }
}

bool graph_visited(const Graph *g, uint32_t v) {
    return g->visited[v];
}

char **graph_get_names(const Graph *g) {
    return g->names;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    return g->names[v];
}

/*
 *
 * void graph_print(const Graph *g) {
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            printf("Start: %s, End: %s, Weight: %u", g->names[i], g->names[j], g->weights[i][j]);
        }
    }
}

*/
