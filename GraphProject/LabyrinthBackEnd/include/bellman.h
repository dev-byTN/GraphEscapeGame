#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

#ifndef BELLMAN_H
#define BELLMAN_H

void display(int arr[], int size);
int BellmanFord(Graphe *graph, int source, int end);

#endif