#include <stdio.h>
#include <stdlib.h>

#ifndef GRAPH_H
#define GRAPH_H

typedef struct ListSuccessor ListSuccessor;
typedef struct Successor Successor;

struct ListSuccessor {
    int size;
    Successor *firstSuccessor;
};

struct Successor {
    int sommet;
    Successor *nextSuccessor;
};

typedef struct Arc {
    int sommet1;
    int sommet2;
    int weight;
} Arc;

typedef struct Graphe {
    int order;
    int nbArcs;
    Arc *arcs;
} Graphe;

ListSuccessor *createList();
void insertHead(ListSuccessor *list, Successor *element);
void insertElement(ListSuccessor *list, Successor *element);
void freeList(ListSuccessor *list);

#endif