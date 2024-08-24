#include <stdio.h>
#include <limits.h>

// Define the number of vertices in the graph
#define V 4

// A utility function to print the solution matrix
void printSolution(int dist[][V]);

// Function to implement Floyd-Warshall algorithm
void floydWarshall(int graph[][V])
{
    int dist[V][V], i, j, k;

    // Initialize the solution matrix same as input graph matrix.
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Adding vertices individually
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j] && (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

// A utility function to print the solution matrix
void printSolution(int dist[][V])
{
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INT_MAX)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Main function to test the implementation
int main()
{
    /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
       \|/         | 1
       (1)------->(2)
            3
    */
    int graph[V][V] = {{0, 5, INT_MAX, 10},
                       {INT_MAX, 0, 3, INT_MAX},
                       {INT_MAX, INT_MAX, 0, 1},
                       {INT_MAX, INT_MAX, INT_MAX, 0}};

    // Print the solution
    floydWarshall(graph);
    return 0;
}
