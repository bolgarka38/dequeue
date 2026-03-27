#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

struct node {
    double data;
    struct node *next;
    struct node *prev;
};
struct deque {
    struct node *front;
    struct node *back;
};
typedef struct deque deque;

// работа с очередью
deque *deque_init(void);
void deque_free(deque *d);
deque *deque_copy(const deque *d);
int deque_push_front(deque *d, double data);
int deque_push_back(deque *d, double data);
int deque_pop_front(deque *d, double *data);
int deque_pop_back(deque *d, double *data);
int deque_is_empty(const deque *d);
void deque_print(const deque *d);

// работа с массивом очередей
int create_new_deque(deque *deques[], int *next_id);
int copy_deque(deque *deques[], int src_id, int *next_id);
deque* get_deque(deque *deques[], int id);
void free_all_deques(deque *deques[]);
void print_all_deques(const deque *deques[]);

#endif // DEQUE_H_INCLUDED
