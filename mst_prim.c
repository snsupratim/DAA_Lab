#include <stdio.h>
#include <limits.h>

// #define vertex 6

int minKey(int key[], int mstSet[], int vertex)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertex; v++)
    {
        if (mstSet[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(int parent[], int graph[][100], int vertex)
{
    int min_weight = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertex; i++)
    {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        min_weight += graph[i][parent[i]];
    }
    printf("%d", min_weight);
}

void primMST(int graph[][100], int vertex)
{
    int parent[vertex];
    int key[vertex];
    int mstSet[vertex];

    for (int i = 0; i < vertex; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < vertex - 1; count++)
    {
        int u = minKey(key, mstSet, vertex);
        mstSet[u] = 1;

        for (int v = 0; v < vertex; v++)
        {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, vertex);
}

int main()
{
    // int graph[vertex][vertex] = {
    //     {0, 6, 1, 5, 0, 0},
    //     {6, 0, 5, 0, 3, 0},
    //     {1, 5, 0, 5, 6, 4},
    //     {5, 0, 5, 0, 0, 2},
    //     {0, 3, 6, 0, 0, 6},
    //     {0, 0, 4, 2, 6, 0}};

    int vertex;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertex);

    int graph[100][100];
    printf("Enter the adjacency matrix of the graph:\n");
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, vertex);

    return 0;
}
