#include <stdio.h>
#include <cs50.h>

typedef struct node {
    char word[46];
    struct node *next;
} node;

const unsigned int N = 10;

// Hash table
node *table[N];

int main(void) {
    char word[46];
    word[0] = 'H';
    word[1] = '\0';
    node n = {.next = nullptr, .word = "Hello"};
    table[0] = &n;
    if (table[0]->next == NULL) {
        printf("NULL\n");
    }
    return 0;
}
