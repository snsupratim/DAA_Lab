#include <stdio.h>
#define MAX 5

int place(int v, int graph[MAX][MAX], int path[], int pos) {
	int i;
  if (graph[path[pos - 1]][v] == 0) {
    return 0;
  }
  for ( i = 0; i < pos; i++) {
    if (path[i] == v) {
      return 0;
    }
  }
  return 1;
}

void ham_all(int graph[MAX][MAX], int path[], int pos) {
	int v,i;
  if (pos == MAX) {
    if (graph[path[pos - 1]][path[0]] == 1) {
      // Print the solution (all path elements are filled)
      printf("Solution exists: ");
      for ( i = 0; i < MAX; i++) {
        printf("%d ", path[i]);
      }
      printf("%d\n", path[0]);
    }
    return;
  }
  for ( v = 1; v < MAX; v++) {
    if (place(v, graph, path, pos)) {
      path[pos] = v;
      ham_all(graph, path, pos + 1);
      // Backtrack (remove v from path)
      path[pos] = -1;
    }
  }
}

int hamcycle(int graph[MAX][MAX]) {
  int path[MAX],i;
  for ( i = 0; i < MAX; i++) {
    path[i] = -1;
  }
  path[0] = 0;
  printf("Following are all Hamiltonian Cycles:\n");
  ham_all(graph, path, 1);
  return 1;
}

int main() {
  int graph[MAX][MAX] = {
    {0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1},
    {1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0}
  };
  hamcycle(graph);
  return 0;
}
