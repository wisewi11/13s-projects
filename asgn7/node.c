#include "node.h"

#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint32_t weight) {
    Node *n = malloc(sizeof(Node));
    n->code = 0;
    n->left = NULL;
    n->right = NULL;
    n->code_length = 0;
    n->symbol = symbol;
    n->weight = weight;

    return n;
}

void node_free(Node **node) {
    if ((*node)->right || (*node)->left) {
        if ((*node)->right != NULL) {
            node_free(&((*node)->right));
            (*node)->right = NULL;
        }
        if ((*node)->left != NULL) {
            node_free(&((*node)->left));
            (*node)->left = NULL;
        }
    }

    free(*node);
    *node = NULL;
}

void node_print_node(Node *tree, char ch, int indentation) {
    if (tree) {
        node_print_node(tree->right, '/', indentation + 3);
        printf("%*cweight = %d", indentation + 1, ch, tree->weight);

        if (tree->left == NULL && tree->right == NULL) {
            if (' ' <= tree->symbol) {
                if (tree->symbol <= '~') {
                    printf(", symbol = '%c'", tree->symbol);
                }
            } else {
                printf(", symbol = 0x%02x", tree->symbol);
            }
        }

        printf("\n");
        node_print_node(tree->left, '\\', indentation + 3);
    }
}

void node_print_tree(Node *tree) {
    node_print_node(tree, '<', 2);
}
