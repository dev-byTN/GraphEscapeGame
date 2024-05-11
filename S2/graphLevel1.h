#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#ifndef GRAPH_LEVEL_1_INCLUDED
#define GRAPH_LEVEL_1_INCLUDED
#define NB_MONSTER 16

typedef struct Monster Monster;
typedef struct GraphMonster GraphMonster;
typedef struct ListMonster ListMonster;


struct GraphMonster
{
    //int nextvertex;
    Monster* monsterType; //weight
    
};

struct Monster
{
    int **adjency;
    int monsterType;
    int nextvertex;
    Monster* next;
};

struct ListMonster
{
    Monster* head;
    int nbVertex;
};


#endif
