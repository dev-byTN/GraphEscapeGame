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
void dijkstra(Graphe* graph, int source) {
    int* distance = malloc(graph->order * sizeof(int));
    bool* visited = malloc(graph->order * sizeof(bool));
    int* parent = malloc(graph->order * sizeof(int));

    for (int i = 0; i < graph->order; i++) {
        parent[0] = -1;
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[source] = 0;
    for (int i = 0; i < graph->order - 1; i++) {
        int U = minimumDistance(distance, visited, graph->order);
        visited[U] = true;
        for (int j = 0; j < graph->order; j++) {
            int curr_distance = distance[U] + graph->adjency[U][j];
            if (!visited[j] && graph->adjency[U][j] && curr_distance < distance[j]) {
                parent[j] = U;
                distance[j] = curr_distance;
            }
        }
    }
    printf("Vertex\t\tDistance\tPath\n");
    for (int i = 1; i < graph->order; i++) {
        printf("%d->%d\t\t%d\t\t%d ", source + 1, i + 1, distance[i], source + 1);
        printParentPath(parent, i);
        printf("\n");
    }
}
