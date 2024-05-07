#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#ifndef GRAPH_LEVEL_1_INCLUDED
#define GRAPH_LEVEL_1_INCLUDED

typedef struct Monster Monster;
typedef struct ListMonster listMonster;
typedef struct Graph Graph;


struct Monster
{
    int vertex;
    int monsterType; //weight
    Monster* next;
};

struct ListMonster
{
    Graph* head;
};

struct Graph
{
    Monster **adjency;
    int vertex;
};


#endif
