#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];
int candidate_count;

bool vote(string name); // Update vote totals given a new vote
void print_winner(void); //prints the winner or winners

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

bool vote(string name)
{
    bool validity = false;
    char *voteName = name;
    for (int i = 0; i < candidate_count; i++)
    {
        char *candidateName = candidates[i].name;
        int voteValidity = strcmp(voteName, candidateName);
        if (voteValidity == 0)
        {
            validity = true;
            candidates[i].votes++;
            break;
        }
    }
    return validity;
}

void print_winner(void)
{
    int maxVote = 0;
    int winnersIndex[MAX];
    int winnersCount = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maxVote)
        {
            maxVote = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maxVote)
        {
            winnersCount++;
            winnersIndex[winnersCount - 1] = i;

        }
    }
    for (int i = 0; i < winnersCount; i++)
    {
        int index = winnersIndex[i];
        printf("%s\n", candidates[index].name);
    }
    return;
}
