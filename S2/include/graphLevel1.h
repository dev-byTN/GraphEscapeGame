#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#ifndef GRAPH_LEVEL_1_INCLUDED
#define GRAPH_LEVEL_1_INCLUDED
#define NB_MONSTER 16

typedef struct Monster Monster;
typedef struct GraphMonster GraphMonster;
typedef struct ListMonster ListMonster;

enum MonsterType {
    ZOMBIE, VAMPIRE
};


struct GraphMonster
{
    int **adjency;
    ListMonster* listMonster;
    //int nextvertex;

};

struct Monster
{
    enum MonsterType monsterType; //weight
    int nextvertex;
    Monster* next;
};

struct ListMonster
{
    Monster* head;
    int nbVertex;
};


#endif
