#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

int minimumDistance(int* distance, bool* visited, int graphSize);
void printParentPath(int parent[], int i);
void dijkstra(Graphe* graph, int source);
void dijkstraMax(Graphe* graph, int source);

#endif