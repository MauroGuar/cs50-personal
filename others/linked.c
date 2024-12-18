#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef struct node {
    int number;
    struct node *next;
} node;

int main() {
    int numbers[] = {1, 2, 3};
    short numbers_size = sizeof(numbers) / sizeof(numbers[0]);

    node *list = NULL;
    for (int i = 0; i < numbers_size; ++i) {
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return 1;
        }
        n->number = numbers[i];
        n->next = NULL;
        if (list == NULL) {
            list = n;
        } else {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next) {
                if (ptr->next == NULL) {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    for (node *ptr = list; ptr != NULL; ptr = ptr->next) {
        printf("%i\n", ptr->number);
    }

    while (list != NULL) {
        node *temp = list;
        list = list->next;
        free(temp);
    }

    return 0;
}
