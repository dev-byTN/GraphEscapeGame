#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GRAPH_H
#define GRAPH_H

typedef struct ListSuccessor ListSuccessor;
typedef struct Successor Successor;

struct ListSuccessor {
    int size;
    Successor *firstSuccessor;
};

struct Successor {
    void* element;
    Successor *nextSuccessor;
};

typedef struct Arc {
    int sommet1;
    int sommet2;
    int weight;
    int color;
    int id;
} Arc;

typedef struct Graphe {
    int order;
    int nbArcs;
    int **adjency;
    Arc *arcs;
    ListSuccessor *arcsList;
} Graphe;

ListSuccessor *createList();
void insertHead(ListSuccessor *list, Successor *element);
void insertElement(ListSuccessor *list, Successor *element);
void removeElement(ListSuccessor *list, Successor *element);
void freeList(ListSuccessor *list);

#endif
