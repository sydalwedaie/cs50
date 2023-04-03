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
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// number of pairs in the array `pairs`
int pair_count;
// number of candidates in the array `candidates`
int candidate_count;

// Function prototypes
void print_array(int array[], int size);
void print_matrix(int matrix[][MAX], int size);
void print_pairs_array(pair array[], int size);

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs (sets initial graph with no edges)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        // each users generates an array of size candidate_count where thier
        // preference is stored. This is is then fed one by one to record_preferences
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        print_array(ranks, candidate_count); // remove

        record_preferences(ranks);
        printf("\n");
    }

    printf("Preferences Matrix: \n");
    print_matrix(preferences, candidate_count); // remove

    add_pairs();
    print_pairs_array(pairs, candidate_count * (candidate_count - 1) / 2); // remove

    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}




// Helper functions
void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}

void print_matrix(int matrix[][MAX], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_pairs_array(pair array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Winner: %i\n", pairs[i].winner);
        printf("Loser:  %i\n", pairs[i].loser);
    }
    printf("\n");
}





// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int swap_counter = -1;

    // This condition would return false only when there was no swap left,
    // which means the array has been sorted
    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int pair_strength_1 = preferences[pairs[i].winner][pairs[i].loser];
            int pair_strength_2 = preferences[pairs[i + 1].winner][pairs[i +1].loser];

            pair pair_1 = pairs[i];
            pair pair_2 = pairs[i + 1];

            // comparing adjacent paris
            if (pair_strength_1 < pair_strength_2)
            {
                // swapping the pairs
                pairs[i] = pair_2;
                pairs[i + 1] = pair_1;

                // if an entire inner loop ends without this line executing,
                // swap_counter remains zero and the outer, while loop would stop
                swap_counter++;
            }
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        int current_pair_strength = preferences[pairs[i].winner][pairs[i].loser];
        printf("Pair %i strength is: %i\n", i, current_pair_strength);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

