#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);

void record_preferences(int ranks[]);

void add_pairs(void);

void sort_pairs(void);

void lock_pairs(void);

bool check_cycle(int winner, int loser);

void print_winner(void);

int main(int argc, string argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; ++i) {
        if (strcasecmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; ++i) {
        for (int j = i + 1; j < candidate_count; ++j) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    int counter = 0;
    for (int i = 0; i < candidate_count; ++i) {
        for (int j = 0; j < candidate_count; ++j) {
            if (i == j) {
                continue;
            }
            int pair_one = preferences[i][j];
            int pair_two = preferences[j][i];
            if (pair_one > pair_two) {
                pair pair = {i, j};
                pairs[counter] = pair;
                counter++;
            } else if (pair_one < pair_two) {
                pair pair = {j, i};
                pairs[counter] = pair;
                counter++;
            }
        }
    }
    pair_count = counter;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    for (int i = 0; i < pair_count - 1; ++i) {
        int max[] = {-1, i};
        for (int j = i; j < pair_count; ++j) {
            int difference = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].
                                 winner];
            if (difference > max[0]) {
                max[0] = difference;
                max[1] = j;
            }
        }
        pair tmp = pairs[i];
        pairs[i] = pairs[max[1]];
        pairs[max[1]] = tmp;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
    for (int i = 0; i < pair_count; ++i) {
        if (!check_cycle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool check_cycle(int winner, int loser) {
    if (winner == loser) {
        return true;
    }
    for (int i = 0; i < candidate_count; ++i) {
        if (locked[loser][i]) {
            if (check_cycle(winner, i)) {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void) {
    for (int i = 0; i < candidate_count; ++i) {
        bool isWinner = true;
        for (int j = 0; j < candidate_count; ++j) {
            if (locked[j][i]) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) {
            printf("%s", candidates[i]);
        }
    }
}
