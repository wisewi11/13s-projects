#include "pq.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->list = NULL;
    return pq;
}

void pq_free(PriorityQueue **q) {
    while (!pq_is_empty(*q)) {
        ListElement *l = (*q)->list;
        (*q)->list = l->next;

        if (!(l->tree)) {
            node_free(&(l->tree));
            l->tree = NULL;
        }

        free(l);
    }

    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
    return q->list == NULL;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        return false;
    } else {
        return !(q->list->next);
    }
}

bool pq_less_than(Node *n1, Node *n2) {
    if (n1->weight > n2->weight) {
        return false;
    } else if (n1->weight < n2->weight) {
        return true;
    } else {
        return n1->symbol < n2->symbol;
    }
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *nl = malloc(sizeof(ListElement));

    nl->tree = tree;
    nl->next = NULL;

    if (pq_is_empty(q)) {
        q->list = nl;
        return;
    }

    ListElement *sl = q->list;

    if (pq_less_than(nl->tree, sl->tree)) {
        nl->next = sl;
        q->list = nl;
        return;
    }

    ListElement *nel = sl->next;

    while (nel != NULL && pq_less_than(nel->tree, nl->tree)) {
        sl = nel;
        nel = nel->next;
    }

    sl->next = nl;
    nl->next = nel;
}

Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        fprintf(stderr, "cannot close queue");
        return NULL;
    }

    ListElement *l = q->list;

    q->list = l->next;
    Node *tree = l->tree;
    free(l);

    return tree;
}
