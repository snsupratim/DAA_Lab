#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int deadline;
    int profit;
} Job;

int compare(const void *a, const void *b)
{
    Job *jobs1 = (Job *)a;
    Job *jobs2 = (Job *)b;
    return jobs2->profit - jobs1->profit;
}

int findmaxdeadline(Job jobs[], int n)
{
    int max = jobs[0].deadline;

    for (int i = 0; i < n; i++)
    {
        if (jobs[i].deadline > max)
        {
            max = jobs[i].deadline;
        }
    }
    return max;
}

void jobscheduling(Job jobs[], int n)
{

    qsort(jobs, n, sizeof(jobs), compare);

    int maxdeadline = findmaxdeadline(jobs, n);

    // create slots to take jobs...

    int *slot = (int *)malloc((maxdeadline + 1) * sizeof(int));
    for (int i = 0; i < maxdeadline; i++)
    {
        slot[i] = -1;
    }

    int totalprofit = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = maxdeadline; j > 0; j--)
        {
            if (slot[j] == -1)
            {
                slot[j] = jobs[i].id;
                totalprofit += jobs[i].profit;
                break;
            }
        }
    }
    printf("scheduled jobs:");
    for (int i = 0; i < maxdeadline; i++)
    {
        if (slot[i] != -1)
        {
            printf("%d", slot[i]);
        }
    }
    printf("totalprofit:%d", totalprofit);
    free(slot);
}

int main()
{
    int n;
    printf("enter number of jobs:");
    scanf("%d", &n);

    Job *jobs = (Job *)malloc(n * sizeof(Job));
    printf("enter values into it:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Job%d:", i + 1);
        scanf("%d %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobscheduling(jobs, n);

    free(jobs);

    return 0;
}
