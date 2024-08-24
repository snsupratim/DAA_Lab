#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble(int **edges, int E)
{
    for (int i = 0; i < E - 1; i++)
    {
        for (int j = 0; j < E - i - 1; j++)
        {
            if (edges[j][2] > edges[j + 1][2])
            {
                int *temp = edges[j][2];
                edges[j][2] = edges[j + 1][2];
                edges[j + 1][2] = temp;
            }
        }
    }
}

int parent(int par[], int v)
{
    if (par[v] == v)
    {
        return v;
    }
    else
    {
        return parent(par, par[v]);
    }
}

void kruskal(int **edges, int V, int E)
{
    int par[V];
    int mstSet[E];

    for (int i = 0; i < E; i++)
    {
        mstSet[i] = false;
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
        int w = edges[i][2];
        int parU = parent(par, u);
        int parV = parent(par, v);
        if (parU != parV)
        {
            r[e][0] = u;
            r[e][1] = v;
            r[e][2] = w;
            e++;
            par[parV] = parU;
            t = t + w;
        }
    }

    printf("edges of mst:\n");
    for (int i = 0; i < V - 1; i++)
    {
        printf("%d - %d -> %d \n", &r[i][0], &r[i][1], &r[i][2]);
    }
    printf("total weight:%d\n", t);
}

int main()
{
    int V, E;
    printf("enter vertex and edges: ");
    scanf("%d %d", &V, &E);

    int **edges = (int **)malloc(E * sizeof(int *));
    for (int i = 0; i < E; i++)
    {
        edges[i] = (int *)malloc(3 * sizeof(int));
    }
    printf("enter values:\n");
    for (int i = 0; i < E; i++)
    {
        sanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }
    bubble(edges, , E);
    kruskal(edges, V, E);
    for (int i = 0; i < E; i++)
    {
        free(edges[i]);
    }
    free(edges);
}