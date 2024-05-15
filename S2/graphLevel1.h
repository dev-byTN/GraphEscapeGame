#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "raylib.h"

#ifndef GRAPH_LEVEL_1_INCLUDED
#define GRAPH_LEVEL_1_INCLUDED
#define NB_MONSTER 16
#define NB_EDGE 45

typedef struct Graph Graph;
typedef struct ListMonster ListMonster;
typedef struct Arc Arc;


/*struct GraphMonster
{
    //int nextvertex;
    Monster* monsterType; //weight
    
};*/

struct Graph
{
    int **adjency;
    Arc *arrayArc;
    Graph* next;
    int tv;
    int te;
};

struct Arc
{
    int u;
    int v;
    int w;
};

struct ListMonster
{
    Graph* head;
};


#endif
