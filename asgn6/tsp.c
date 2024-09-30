#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void dfs(Path *current, Path *shortest, Graph *g, uint32_t v, FILE *ofile) {
    graph_visit_vertex(g, v);
    Path *p = current;
    path_add(p, v, g);

    if (path_vertices(p) == graph_vertices(g) && graph_get_weight(g, v, START_VERTEX)) {
        path_add(p, START_VERTEX, g);
        if (path_distance(p) < path_distance(shortest) || path_vertices(shortest) == 0) {
            path_copy(shortest, p);
            return;
        }
    }

    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        if (!graph_visited(g, i) && graph_get_weight(g, v, i)) {
            dfs(current, shortest, g, i, ofile);
        }
    }

    graph_unvisit_vertex(g, v);
    path_remove(p, g);
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool directed = false;

    int opt;
    uint32_t num_vertices;
    uint32_t num_edges;
    uint32_t start;
    uint32_t end;
    uint32_t weight;

    while ((opt = getopt(argc, argv, "i:o:dh")) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r");
            if (infile != NULL) {
                break;
            }

            else {
                fprintf(stderr, "infile is NULL\n");
                return 1;
            }
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile != NULL) {
                break;
            }

            else {
                fprintf(stderr, "outfile is NULL\n");
                return 1;
            }
        case 'd': directed = true; break;
        case 'h':
            printf("Usage: tsp [options]\n\n");
            printf("-i infile    Specify the input file path containing the cities and edges\n");
            printf("             of a graph. If not specified, the default input should be\n");
            printf("             set as stdin.\n\n");
            printf("-o outfile   Specify the output file path to print to. If not specified,\n");
            printf("             the default output should be set as stdout.\n\n");
            printf("-d           Specifies the graph to be directed.\n\n");
            printf("-h           Prints out a help message describing the purpose of the\n");
            printf("             graph and the command-line options it accepts, exiting the\n");
            printf("             program afterwards.\n");
            return 0;
        case '?':
            fprintf(stderr, "tsp:  unknown or poorly formatted option -%c\n", optopt);
            return 1;
        }
    }

    fscanf(infile, "%u", &num_vertices);
    fgetc(infile);

    Graph *g = graph_create(num_vertices, directed);

    for (uint32_t i = 0; i < num_vertices; i++) {
        graph_unvisit_vertex(g, i);
    }

    for (uint32_t i = 0; i < num_vertices; i++) {
        char name[100];
        if (fgets(name, sizeof(name), infile)) {
            name[strcspn(name, "\n")] = '\0';
            graph_add_vertex(g, name, i);
        } else {
            fprintf(stderr, "ERROR: Vertex name error\n");
        }
    }

    fscanf(infile, "%u", &num_edges);
    fgetc(infile);

    for (uint32_t edge = 0; edge < num_edges; edge++) {
        fscanf(infile, "%u %u %u", &start, &end, &weight);
        fgetc(infile);
        graph_add_edge(g, start, end, weight);
    }

    Path *current_path = path_create(num_vertices + 1);
    Path *min_path = path_create(num_vertices + 1);

    start = START_VERTEX;

    dfs(current_path, min_path, g, start, outfile);

    if (path_distance(min_path) > 0) {
        printf("Alissa starts at:\n");
        path_print(min_path, outfile, g);
        fprintf(outfile, "Total Distance: %u\n", path_distance(min_path));
    }

    else {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    }

    fclose(outfile);
    fclose(infile);
    path_free(&current_path);
    path_free(&min_path);
    graph_free(&g);
    return 0;
}
