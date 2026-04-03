#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deque.h"

#define MAX_DEQUES 10

int main() {
    deque *deques[MAX_DEQUES] = {NULL};
    int current_id = -1;
    int next_id = 0;
    char command[20];
    int id;
    double data;
    int res;

    printf("Deque on a doubly linked list\n");
    printf("Commands:\n");
    printf("  new               - create new empty queue\n");
    printf("  copy <id>         - create copy of queue with id number\n");
    printf("  select <id>       - select queue with id number\n");
    printf("  push_front <val>  - push new value to the start of the selected queue\n");
    printf("  push_back <val>   - push new value to the end of the selected queue\n");
    printf("  pop_front         - pop value from the start of the selected queue\n");
    printf("  pop_back          - pop value from the end of the selected queue\n");
    printf("  print             - print selected queue\n");
    printf("  print_all         - print all queues\n");
    printf("  quit              - quit\n\n");

    while (1) {
        printf("> ");
        if (scanf("%s", command) != 1) break;
        if (strcmp(command, "new") == 0) {
            res = create_new_deque(deques, &next_id);
            if (res >= 0)
                printf("Queue with number created %d\n", res);
            else
                printf("Error: can't create new queue (max %d)\n", MAX_DEQUES);
        }
        else if (strcmp(command, "copy") == 0) {
            if (scanf("%d", &id) != 1) {
                printf("Input error\n");
                continue;
            }
            res = copy_deque(deques, id, &next_id);
            if (res >= 0)
                printf("A copy of the queue with number %d has been created \n", id);
            else if (res == -1)
                printf("Error: original queue %d don't exist\n", id);
            else
                printf("Error: can't create new queue (max %d)\n", MAX_DEQUES);
        }
        else if (strcmp(command, "select") == 0) {
            if (scanf("%d", &id) != 1) {
                printf("Input error\n");
                continue;
            }
            if (id >= 0 && id < MAX_DEQUES && deques[id] != NULL) {
                current_id = id;
                printf("Queue selected %d\n", current_id);
            } else {
                printf("Queue with number %d don't exist\n", id);
            }
        }
        else if (strcmp(command, "push_front") == 0) {
            if (current_id == -1) {
                printf("Select queue with 'select' first\n");
                continue;
            }
            if (scanf("%lf", &data) != 1) {
                printf("Input error\n");
                continue;
            }
            if (deque_push_front(deques[current_id], data) == 0)
                printf("Pushed %.2f in the queue %d start \n", data, current_id);
            else
                printf("Push error\n");
        }
        else if (strcmp(command, "push_back") == 0) {
            if (current_id == -1) {
                printf("Select queue with 'select' first\n");
                continue;
            }
            if (scanf("%lf", &data) != 1) {
                printf("Input error\n");
                continue;
            }
            if (deque_push_back(deques[current_id], data) == 0)
                printf("Pushed %.2f in the queue %d end \n", data, current_id);
            else
                printf("Push error\n");
        }
        else if (strcmp(command, "pop_front") == 0) {
            if (current_id == -1) {
                printf("Select queue with 'select' first\n");
                continue;
            }
            if (deque_pop_front(deques[current_id], &data) == 0)
                printf("Poped %.2f from the queue %d start \n", data, current_id);
            else
                printf("Error: queue is empty\n");
        }
        else if (strcmp(command, "pop_back") == 0) {
            if (current_id == -1) {
                printf("Select queue with 'select' first\n");
                continue;
            }
            if (deque_pop_back(deques[current_id], &data) == 0)
                printf("Poped %.2f from the queue %d end \n", data, current_id);
            else
                printf("Eror: queue is empty\n");
        }
        else if (strcmp(command, "print") == 0) {
            if (current_id == -1) {
                printf("Select queue with 'select' first\n");
                continue;
            }
            printf("Queue %d: ", current_id);
            deque_print(deques[current_id]);
            printf("\n");
        }
        else if (strcmp(command, "print_all") == 0) {
            print_all_deques((const deque**)deques);
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }
        else {
            printf("Unknown command\n");
        }
        while (getchar() != '\n');
    }

    free_all_deques(deques);
    return 0;
}

