#include <stdio.h>
#include <cs50.h>

#define CAND_COUNT 4

bool check_cycle(int winner, int loser);

char candidates[CAND_COUNT] = {"A", "B", "C", "D"};
bool locked[CAND_COUNT][CAND_COUNT];

int main(void) {
    for (int i = 0; i < CAND_COUNT; i++) {
        for (int j = 0; j < CAND_COUNT; j++) {
            locked[i][j] = false;
        }
    }
    locked[0][1] = true;
    locked[1][2] = true;
    locked[2][3] = true;

    for (int i = 0; i < CAND_COUNT; i++) {
        visited[i] = false;
    }

    if (check_cycle(3, 0)) {
        printf("Cycle detected\n");
    } else {
        printf("No cycle detected\n");
    }
    return 0;
}

bool check_cycle(int winner, int loser) {
    if (winner == loser) {
        return true;
    }

    for (int i = 0; i < CAND_COUNT; ++i) {
        if (locked[loser][i]) {
            if (check_cycle(winner, i)) { return true; }
        }
    }
    return false;
}
