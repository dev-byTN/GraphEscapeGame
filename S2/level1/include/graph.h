#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "raylib.h"
#include "/home/trx/INFO2A/PROJET/S2/level1/json/json.h"
#pragma once

#ifndef GRAPH_H
#define GRAPH_H
#define NB_MONSTER 16
#define NB_EDGE 45

typedef struct ListSuccessor ListSuccessor;
typedef struct Successor Successor;
typedef struct Arc Arc;
typedef struct Graph2 Graph2;

struct ListSuccessor {
    int size;
    Successor *firstSuccessor;
};

struct Successor {
    int sommet;
    Successor *nextSuccessor;
};

struct Arc {
    int sommet1;
    int sommet2;
    int weight;
};

struct Graph2 {
    int order;
    int nbArcs;
    int **adjency;
    Arc *arcs;
};

ListSuccessor *createList();
void insertHead(ListSuccessor *list, Successor *element);
void insertElement(ListSuccessor *list, Successor *element);
void freeList(ListSuccessor *list);

#endif
