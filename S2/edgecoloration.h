#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

#ifndef EDGECOLORATION_H
#define EDGECOLORATION_H

bool isAlreadyAdded(Arc *arc, ListSuccessor *list);
ListSuccessor *getOneWayArcsList(ListSuccessor *arcsList);
ListSuccessor *getAdjacentArcs(ListSuccessor *arcsList, Arc *arc);
int edgeColoration(Graphe *graph, int source);
char* getColorFromIntValue(int value);

#endif