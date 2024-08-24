#include <stdio.h>
#include <stdlib.h>

double fractionalKnapsack(int W, int values[], int weights[], int n)
{
    double ratios[n];
    int i, j;
    for (i = 0; i < n; i++)
    {
        ratios[i] = (double)values[i] / weights[i];
    }

    double totalValue = 0.0;
    int currentWeight = 0;

    for (i = 0; i < n; i++)
    {
        int maxIndex = 0;
        double maxRatio = 0;
        for (j = 0; j < n; j++)
        {
            if (ratios[j] > maxRatio)
            {
                maxRatio = ratios[j];
                maxIndex = j;
            }
        }

        if (currentWeight + weights[maxIndex] <= W)
        {
            currentWeight += weights[maxIndex];
            totalValue += values[maxIndex];
            ratios[maxIndex] = 0; // Marking item as used
        }
        else
        {
            int remainingWeight = W - currentWeight;
            totalValue += values[maxIndex] * ((double)remainingWeight / weights[maxIndex]);
            break;
        }
    }

    return totalValue;
}

int main()
{
    int n, capacity, i;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int values[n], weights[n];

    printf("Enter the values and weights of each item:\n");
    for (i = 0; i < n; i++)
    {
        printf("Value of item %d: ", i + 1);
        scanf("%d", &values[i]);
        printf("Weight of item %d: ", i + 1);
        scanf("%d", &weights[i]);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    double maxValue = fractionalKnapsack(capacity, values, weights, n);

    printf("Maximum value we can obtain = %.2f\n", maxValue);

    return 0;
}
