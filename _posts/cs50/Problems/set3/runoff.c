#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // 遍历所有候选人，查找匹配的名字
    for (int i = 0; i < candidate_count; i++)
    {
        // 比较候选人名字
        if (strcmp(candidates[i].name, name) == 0)
        {
            // 找到了！记录这个选民的第 rank 选择
            // preferences[voter][rank] 存储候选人的索引
            preferences[voter][rank] = i;
            return true;
        }
    }

    // 没找到匹配的候选人
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // 遍历每个选民
    for (int i = 0; i < voter_count; i++)
    {
        // 从该选民的第1选择开始看
        for (int j = 0; j < candidate_count; j++)
        {
            // 获取该选民第 j 选择的候选人索引
            int candidate_index = preferences[i][j];

            // 检查这个候选人是否还在选举中（没被淘汰）
            if (!candidates[candidate_index].eliminated)
            {
                // 给这个候选人加1票
                candidates[candidate_index].votes++;

                // 重要：找到第一个没被淘汰的候选人后就停止
                // 不再看这个选民的后续选择
                break;
            }
            // 如果这个候选人被淘汰了，继续看下一个选择
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // 计算获胜所需的票数（过半数）
    // 如果有5个选民，需要 5/2 + 1 = 3票
    int majority = voter_count / 2 + 1;

    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 检查是否有候选人达到多数票
        if (candidates[i].votes >= majority)
        {
            // 找到赢家，打印名字
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // 没有人获胜
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // 初始化为一个很大的数
    int min_votes = voter_count;

    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 只考虑还在选举中的候选人
        if (!candidates[i].eliminated)
        {
            // 如果这个候选人的票数更少，更新最小值
            if (candidates[i].votes < min_votes)
            {
                min_votes = candidates[i].votes;
            }
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // 检查是否所有剩余候选人的票数都等于 min

    for (int i = 0; i < candidate_count; i++)
    {
        // 只检查没被淘汰的候选人
        if (!candidates[i].eliminated)
        {
            // 如果有任何一个候选人的票数不等于 min
            // 说明不是平局
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }

    // 所有剩余候选人票数都相同，是平局
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // 遍历所有候选人
    for (int i = 0; i < candidate_count; i++)
    {
        // 如果候选人还在选举中，且票数等于最小值
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            // 淘汰这个候选人
            candidates[i].eliminated = true;
        }
    }
}



