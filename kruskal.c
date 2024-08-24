#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to perform bubble sort on the edges based on their weights
void bubble(int **edges, int E)
{
    for (int i = 0; i < E - 1; i++)
    {
        for (int j = 0; j < E - i - 1; j++)
        {
            if (edges[j][2] > edges[j + 1][2])
            {
                int *temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Function to find the parent of a vertex in the disjoint set
int parent(int par[], int v)
{
    if (par[v] == v)
    {
        return v;
    }
    return parent(par, par[v]);
}

// Function to implement Kruskal's algorithm to find the Minimum Spanning Tree (MST)
void kruskal(int **edges, int V, int E)
{
    int par[V];
    bool MST[E];
    for (int i = 0; i < E; i++)
    {
        MST[i] = false;
    }
    for (int i = 0; i < V; i++)
    {
        par[i] = i;
    }

    int r[V - 1][3];
    int e = 0;
    int t = 0;
    for (int i = 0; i < E; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];
        int parU = parent(par, u);
        int parV = parent(par, v);
        if (parU != parV)
        {
            r[e][0] = u;
            r[e][1] = v;
            r[e][2] = weight;
            e++;
            par[parV] = parU;
            t = t + weight;
        }
    }
    printf("Edges of Minimum Spanning Tree:\n");
    for (int i = 0; i < V - 1; i++)
    {
        printf("(%d, %d) -> %d\n", r[i][0], r[i][1], r[i][2]);
    }
    printf("Total weight of MST: %d\n", t);
}

int main()
{
    int V, E;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int **edges = (int **)malloc(E * sizeof(int *));
    for (int i = 0; i < E; i++)
    {
        edges[i] = (int *)malloc(3 * sizeof(int));
    }

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }

    bubble(edges, E);
    kruskal(edges, V, E);

    for (int i = 0; i < E; i++)
    {
        free(edges[i]);
    }
    free(edges);

    return 0;
}
