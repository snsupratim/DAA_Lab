#include <stdio.h>
#include <stdbool.h>
#define MAX 100
#define COLORS 3
char colors[COLORS] = {'R', 'G', 'B'}; 
int graph[MAX][MAX] = 
{
    {0, 1, 1, 0, 0},
    {1, 0, 1, 1, 0},
    {1, 1, 0, 1, 1},
    {0, 1, 1, 0, 1},
    {0, 0, 1, 1, 0}
};
char ac[MAX];
int c = 0;
bool place(int v, char color, int V)
{
	int i;
    for ( i = 0; i < V; i++)
    { 
        if (graph[v][i] && ac[i] == color) 
        {
            return false;
        }
    }
    return true;
}
void printcoloring(int V) 
{
	int i;
    for ( i = 0; i < V; i++) 
    {
        printf("Vertex %d -> Color %c \n", i + 1, ac[i]);
    }
    printf("\n");
    c++;
}
void graphcoloring(int V, int m, int v) 
{
	int c;
    if (v == V) 
    {
        printcoloring(V);
        return;
    }
    for ( c = 0; c < m; c++) 
    {
        if (place(v, colors[c], V))  
        {
            ac[v] = colors[c];
            graphcoloring(V, m, v + 1);
            ac[v] = '\0'; 
        }
    }
}
void graph_coloring(int V) 
{
	int i;
    for ( i = 0; i < V; i++) 
    {
        ac[i] = '\0';
    }
    graphcoloring(V, COLORS, 0);
}
int main()  
{
    int V = 5;
    printf("All possible color combinations:\n");
    graph_coloring(V);
    printf("Total color combinations found: %d\n", c);
    return 0;
}
