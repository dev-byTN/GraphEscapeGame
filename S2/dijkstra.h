#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

int minimumDistance(int* distance, bool* visited, int graphSize);
void printParentPath(int parent[], int i);
void dijkstra(int** graph, int graphSize, int source);

#endif