#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 4
#define MAX 100000

typedef struct Node
{
    int board[N][N];
    int g, h, f;
    int zero_row, zero_col;
    struct Node *parent; // Add a parent pointer to trace the path
} Node;

typedef struct
{
    Node *nodes[MAX];
    int size;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq)
{
    pq->size = 0;
}

bool isPriorityQueueEmpty(PriorityQueue *pq)
{
    return pq->size == 0;
}

void push(PriorityQueue *pq, Node *node)
{
    pq->nodes[pq->size++] = node;
}

Node *pop(PriorityQueue *pq)
{
    int minIndex = 0;
    for (int i = 1; i < pq->size; i++)
    {
        if (pq->nodes[i]->f < pq->nodes[minIndex]->f)
        {
            minIndex = i;
        }
    }
    Node *minNode = pq->nodes[minIndex];
    pq->nodes[minIndex] = pq->nodes[--pq->size];
    return minNode;
}

int manhattanDistance(int start[N][N], int goal[N][N])
{
    int distance = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (start[i][j] != 0)
            {
                for (int x = 0; x < N; x++)
                {
                    for (int y = 0; y < N; y++)
                    {
                        if (start[i][j] == goal[x][y])
                        {
                            distance += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return distance;
}

bool isGoal(int board[N][N], int goal[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] != goal[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool isValidMove(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void copyBoard(int dest[N][N], int src[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

void printBoard(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printSolution(Node *node)
{
    if (node == NULL)
        return;
    printSolution(node->parent);
    printBoard(node->board);
}

bool solvePuzzle(int start[N][N], int goal[N][N])
{
    PriorityQueue pq;
    initPriorityQueue(&pq);

    Node *startNode = (Node *)malloc(sizeof(Node));
    if (startNode == NULL)
    {
        printf("Memory allocation failed\n");
        return false;
    }
    copyBoard(startNode->board, start);
    startNode->g = 0;
    startNode->h = manhattanDistance(start, goal);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = NULL;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (startNode->board[i][j] == 0)
            {
                startNode->zero_row = i;
                startNode->zero_col = j;
                break;
            }
        }
    }

    push(&pq, startNode);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!isPriorityQueueEmpty(&pq))
    {
        Node *current = pop(&pq);

        if (isGoal(current->board, goal))
        {
            printf("Solution found!\n");
            printSolution(current);
            // Free allocated memory
            while (current)
            {
                Node *temp = current;
                current = current->parent;
                free(temp);
            }
            return true;
        }

        for (int i = 0; i < 4; i++)
        {
            int newRow = current->zero_row + dx[i];
            int newCol = current->zero_col + dy[i];

            if (isValidMove(newRow, newCol))
            {
                Node *next = (Node *)malloc(sizeof(Node));
                if (next == NULL)
                {
                    printf("Memory allocation failed\n");
                    return false;
                }
                copyBoard(next->board, current->board);
                next->board[current->zero_row][current->zero_col] = next->board[newRow][newCol];
                next->board[newRow][newCol] = 0;

                next->g = current->g + 1;
                next->h = manhattanDistance(next->board, goal);
                next->f = next->g + next->h;
                next->zero_row = newRow;
                next->zero_col = newCol;
                next->parent = current;

                push(&pq, next);
            }
        }
    }

    printf("No solution found.\n");
    return false;
}

int main()
{
    int start[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 0, 15}};

    int goal[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}};

    solvePuzzle(start, goal);

    return 0;
}
