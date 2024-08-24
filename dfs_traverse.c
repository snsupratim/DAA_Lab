#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in adjacency list
struct ListNode
{
    int vertex;
    struct ListNode *next;
};

// Structure to represent adjacency list
struct AdjList
{
    struct ListNode *head;
};

// Structure to represent the graph
struct Graph
{
    int numVertices;
    struct AdjList *array;
    int *visited; // Array to keep track of visited vertices
};

// Function to create a new node
struct ListNode *createNode(int vertex)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given vertices
struct Graph *createGraph(int numVertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList *)malloc(numVertices * sizeof(struct AdjList));
    graph->visited = (int *)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; ++i)
    {
        graph->array[i].head = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph *graph, int src, int dest)
{
    struct ListNode *newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Depth-First Search traversal
void DFS(struct Graph *graph, int vertex)
{
    struct ListNode *temp = graph->array[vertex].head;
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL)
    {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex])
        {
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}

// Main function
int main()
{
    int numVertices = 6; // Example graph with 6 vertices

    // Create the graph
    struct Graph *graph = createGraph(numVertices);

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("DFS Traversal: ");
    // Perform DFS traversal
    DFS(graph, 0);

    return 0;
}
