#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEQUES 10

deque *deque_init(void) {
    deque *d = (deque*)malloc(sizeof(deque));
    if (!d) return NULL;
    d->front = d->back = NULL;
    return d;
}

void deque_free(deque *d) {
    if (!d) return;
    struct node *current = d->front;
    while (current) {
        struct node *next = current->next;
        free(current);
        current = next;
    }
    free(d);
}

deque *deque_copy(const deque *d) {
    if (!d) return NULL;
    deque *new_d = deque_init();
    if (!new_d) return NULL;

    struct node *cur = d->front;
    while (cur) {
        if (deque_push_back(new_d, cur->data) != 0) {
            deque_free(new_d);
            return NULL;
        }
        cur = cur->next;
    }
    return new_d;
}

int deque_push_front(deque *d, double data) {
    if (!d) return -1;
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return -1;
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = d->front;

    if (deque_is_empty(d)) {
        d->front = d->back = new_node;
    } else {
        d->front->prev = new_node;
        d->front = new_node;
    }
    return 0;
}

int deque_push_back(deque *d, double data) {
    if (!d) return -1;
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return -1;
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = d->back;

    if (deque_is_empty(d)) {
        d->front = d->back = new_node;
    } else {
        d->back->next = new_node;
        d->back = new_node;
    }
    return 0;
}

int deque_pop_front(deque *d, double *data) {
    if (!d || deque_is_empty(d)) return -1;
    struct node *tmp = d->front;
    *data = tmp->data;
    d->front = tmp->next;
    if (d->front)
        d->front->prev = NULL;
    else
        d->back = NULL;
    free(tmp);
    return 0;
}

int deque_pop_back(deque *d, double *data) {
    if (!d || deque_is_empty(d)) return -1;
    struct node *tmp = d->back;
    *data = tmp->data;
    d->back = tmp->prev;
    if (d->back)
        d->back->next = NULL;
    else
        d->front = NULL;
    free(tmp);
    return 0;
}

int deque_is_empty(const deque *d) {
    return (d == NULL || d->front == NULL);
}

void deque_print(const deque *d) {
    if (!d || deque_is_empty(d)) {
        printf("empty");
        return;
    }
    struct node *cur = d->front;
    while (cur) {
        printf("%.2f ", cur->data);
        cur = cur->next;
    }
}

int create_new_deque(deque *deques[], int *next_id) {
    if (*next_id >= MAX_DEQUES) return -1;
    deque *d = deque_init();
    if (!d) return -1;
    deques[*next_id] = d;
    int new_id = *next_id;
    (*next_id)++;
    return new_id;
}

int copy_deque(deque *deques[], int src_id, int *next_id) {
    if (src_id < 0 || src_id >= MAX_DEQUES || deques[src_id] == NULL)
        return -1;
    if (*next_id >= MAX_DEQUES) return -2;
    deque *copy = deque_copy(deques[src_id]);
    if (!copy) return -2;
    deques[*next_id] = copy;
    int new_id = *next_id;
    (*next_id)++;
    return new_id;
}

void free_all_deques(deque *deques[]) {
    for (int i = 0; i < MAX_DEQUES; i++) {
        if (deques[i]) {
            deque_free(deques[i]);
            deques[i] = NULL;
        }
    }
}

void print_all_deques(const deque *deques[]) {
    int empty = 1;
    for (int i = 0; i < MAX_DEQUES; i++) {
        if (deques[i] != NULL) {
            printf("queue %d: ", i);
            deque_print(deques[i]);
            printf("\n");
            empty = 0;
        }
    }
    if (empty)
        printf("No queues created\n");
}
