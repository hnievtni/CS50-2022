#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
}
pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]); // Update ranks given a new vote
void record_preferences(int ranks[]); // Update preferences given one voter's ranks
void add_pairs(void); // Record pairs of candidates where one is preferred over the other
void sort_pairs(void); // Sort pairs in decreasing order by strength of victory
void lock_pairs(void); // Lock pairs into the candidate graph in order, without creating cycles
void print_winner(void); // Print the winner of the election
bool cycle(int start, int end); //cycle check

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
            preferences[i][j] = 0;
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

bool vote(int rank, string name, int ranks[])
{
    bool validity = false;
    char *voteName = name;
    for (int i = 0; i < candidate_count; i++)
    {
        char *candidateName = candidates[i];
        if (strcmp(voteName, candidateName) == 0)
        {
            validity = true;
            ranks[rank] = i;
            break;
        }
    }
    return validity;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate1 = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int candidate2 = ranks[j];
            preferences[candidate1][candidate2]++;
        }
    }
    return;
}

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
        }
    }
    return;
}

void sort_pairs(void)
{
    int maxPreference = 0, maxIndex = 0;
    for (int count = 0; count < pair_count; count++)
    {
        for (int i = 0; i < pair_count; i++)
        {
            int winner1 = pairs[i].winner, winner2 = pairs[i + 1].winner;
            int loser1 = pairs[i].loser, loser2 = pairs[i + 1].loser;
            int preference1 = preferences[winner1][loser1], preference2 = preferences[winner2][loser2];

            if (preference1 < preference2)
            {
                pairs[i].winner = winner2;
                pairs[i].loser = loser2;
                pairs[i + 1].winner = winner1;
                pairs[i + 1].loser = loser1;
            }
        }
    }
    return;
}

void lock_pairs(void)
{
    for (int count = 0; count < pair_count; count++)
    {
        if (!cycle(pairs[count].winner, pairs[count].loser))
        {
            locked[pairs[count].winner][pairs[count].loser] = true;;
        }
    }
    return;
}
bool cycle(int start, int end)
{
    if (start == end)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i])
        {
            if (cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        int value = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (!locked[i][j])
            {
                value++;
                if (value == candidate_count)
                {
                    printf("%s\n", candidates[j]);
                }
            }
        }
    }
    return;
}
