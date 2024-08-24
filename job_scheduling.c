#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;       // Job ID
    int deadline; // Deadline of job
    int profit;   // Profit if job is completed before or on deadline
} Job;

// Function to compare two jobs according to their profits (for sorting)
int compare(const void *a, const void *b)
{
    Job *job1 = (Job *)a;
    Job *job2 = (Job *)b;
    return job2->profit - job1->profit; // Descending order
}

// Function to find the maximum deadline in the job array
int findMaxDeadline(Job jobs[], int n)
{
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++)
    {
        if (jobs[i].deadline > max)
        {
            max = jobs[i].deadline;
        }
    }
    return max;
}

// Function to perform job sequencing with deadlines to maximize profit
void jobSequencing(Job jobs[], int n)
{
    // Step 1: Sort the jobs by profit in descending order
    qsort(jobs, n, sizeof(Job), compare);

    // Step 2: Find the maximum deadline
    int maxDeadline = findMaxDeadline(jobs, n);

    // Step 3: Create an array to keep track of free time slots
    int *slot = (int *)malloc((maxDeadline + 1) * sizeof(int));
    for (int i = 0; i <= maxDeadline; i++)
    {
        slot[i] = -1; // Initialize all slots to be free
    }

    // Step 4: Schedule the jobs to maximize profit
    int totalProfit = 0;
    for (int i = 0; i < n; i++)
    {
        // Find a free slot for this job (we start from the last possible slot)
        for (int j = jobs[i].deadline; j > 0; j--)
        {
            if (slot[j] == -1)
            {
                slot[j] = jobs[i].id; // Assign this slot to the job
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Display the scheduled jobs and the total profit
    printf("Scheduled Jobs: ");
    for (int i = 1; i <= maxDeadline; i++)
    {
        if (slot[i] != -1)
        {
            printf("|%d| ", slot[i]);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);

    // Free the allocated memory
    free(slot);
}

int main()
{
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job *jobs = (Job *)malloc(n * sizeof(Job));
    printf("Enter job details (id, deadline, profit):\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nJob %d: ", i + 1);
        scanf("%d %d  %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    // Free the allocated memory
    free(jobs);

    return 0;
}
