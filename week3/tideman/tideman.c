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

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle(int winner);
bool dfs(int node, bool visited[], bool inPath[], int parent);
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

    // Clear graph of locked in pairs
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
            // printf("%i\n", ranks[j]);
        }
        record_preferences(ranks);
        printf("\n");

    }
    // for (int m = 0; m < candidate_count; m++)
    // {
    //     for (int k = 0; k < candidate_count; k++)
    //     {
    //         printf("%i ", preferences[m][k]);
    //     }
    //         printf("\n");
    // }
    // printf("\n");

    add_pairs();
    // printf("UNSORTED\n\n");
    // for (int z = 0; z < pair_count; z++)
    // {
    //     printf("Pair: %i\n", z);
    //     printf("W: %i\n", pairs[z].winner);
    //     printf("L: %i\n", pairs[z].loser);
    //     printf("\n");
    // }

    sort_pairs();
    // printf("SORTED\n\n");
    // for (int z = 0; z < pair_count; z++)
    // {
    //     printf("Pair: %i\n", z);
    //     printf("W: %i\n", pairs[z].winner);
    //     printf("L: %i\n", pairs[z].loser);
    //     printf("\n");
    // }

    lock_pairs();
    // for (int m = 0; m < candidate_count; m++)
    // {
    //     for (int k = 0; k < candidate_count; k++)
    //     {
    //         printf("%i ", locked[m][k]);
    //     }
    //         printf("\n");
    // }
    // printf("\n");

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    // Loops through candidates, to checks if name matches a valid candidate
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(name, candidates[i]) == 0)
        {
            // Adds 1 to ranks array at the voters [rank] preference
            ranks[rank] = i;
            return true;
        }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // Fills values of 2D Array with result from ranks[]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            // printf("%i\n", ranks[i]);
            // printf("%i\n", ranks[j]);
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Goes through candidate[i] and candidate[i+1] to determine who is the prefered candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Detremine the strength of victory and sorts pairs array in decreasing order of strength of victory
    pair swap;
    swap.winner = 0;
    swap.loser = 0;

    for (int i = 0, dif1 = 0; i < pair_count; i++)
    {
        // Diffrence of the strength of victory 1
        dif1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];

        for (int j = 0, dif2 = 0; j < pair_count; j++)
        {
            // Diffrence of the strength of victory 2
            dif2 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];

            // If diff strength of pair 1 > diff strength pair2, swap them
            if (dif1 > dif2)
            {
                swap = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = swap;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // loops through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Adds an edge
        // printf("LOCKED\n");
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Check if adding that edge created a cycle.
        if (cycle(pairs[i].winner) == true)
        {
            // If so, unlocks pairs
            // printf("UNLOCKED\n");
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }

    return;
}

// Checks if adding an edge in locked creates a cycle.
bool cycle(int winner)
{
    // Array to keep track of which nodes have been visited
    bool visited[candidate_count];
    bool inPath[candidate_count];

    // Initially set all elemnts of the array to false
    for (int n = 0; n < candidate_count; n++)
    {
        visited[n] = false;
        inPath[n] = false;
    }

    int parent = -1;
    if (dfs(winner, visited, inPath, parent) == false)
    {
        return false;
    }

    return true;
}

bool dfs(int node, bool visited[], bool inPath[], int parent)
{
    visited[node] = true;
    inPath[node] = true;

    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[node][j] == true)
        {
            // This checks if the neighbor j has not been visited yet
            if (!visited[j])
            {
                // If it hasn't, recursively call the DFS function on j
                if (dfs(j, visited, inPath, node))
                {
                    // Returns true if a cycle is found
                    return true;
                }
            }

            // This checks If j is already visited and it's not the parent of the current node
            else if (inPath[j])
            {
                // Returns true if a cycle is found
                return true;
            }
        }
    }
    // No cycle found
    inPath[node] = false;
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Loop through locked array
    int i = 0;
    for (int n = 0; i < candidate_count; i++)
    {
        // reset n at the start of each loop
        n = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if current candidate has ever lost (not the source of graph)
            if (!locked[j][i])
            {
                n++;
            }
        }

        // If # wins = # candidates, they are the source
        if (n == candidate_count)
        {
            break;
        }
    }
    // print winner
    printf("%s\n", candidates[i]);

    return;
}