#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    if (l->head == NULL) {
        l->head = n;
        return true;
    } else {
        Node *tail = l->head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = n;
        return true;
    }
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {

    Node *n = l->head;
    Node *ns = NULL;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            if (ns) {
                ns->next = n->next;
            }

            if (n == l->head) {
                l->head = n->next;
            }
            n->next = NULL;
            free(n);
            break;
        }
        ns = n;
        n = n->next;
    }
}

void list_destroy(LL **l) {

    if (*l) {
        Node *n = (*l)->head;
        Node *nod = NULL;
        while (n != NULL) {
            nod = n->next;
            free(n);
            n = nod;
        }

        free(*l);
        *l = NULL;
    }
}
