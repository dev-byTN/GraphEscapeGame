#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "dijkstra.h"

int minimumDistance(int* distance, bool* visited, int graphSize) {
    int min = INT_MAX;
    int min_index = INT_MAX;
    for (int i = 0; i < graphSize; i++) {
        if (!visited[i] && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}
void printParentPath(int parent[], int i) {
    if (parent[i] == -1) {
        return;
    }
    printParentPath(parent, parent[i]);
    printf("%d ", i + 1);
}
void dijkstra(int** graph, int graphSize, int source) {
    int distance[graphSize];
    bool visited[graphSize];
    int parent[graphSize];
    for (int i = 0; i < graphSize; i++) {
        parent[0] = -1;
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[source] = 0;
    for (int i = 0; i < graphSize - 1; i++) {
        int U = minimumDistance(distance, visited, graphSize);
        visited[U] = true;
        for (int j = 0; j < graphSize; j++) {
            int curr_distance = distance[U] + graph[U][j];
            if (!visited[j] && graph[U][j] && curr_distance < distance[j]) {
                parent[j] = U;
                distance[j] = curr_distance;
            }
        }
    }
    printf("Vertex\t\tDistance\tPath\n");
    for (int i = 1; i < graphSize; i++) {
        printf("%d->%d\t\t%d\t\t%d ", source + 1, i + 1, distance[i], source + 1);
        printParentPath(parent, i);
        printf("\n");
    }
}
