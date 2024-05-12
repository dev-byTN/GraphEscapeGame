#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NB_EDGE 45
#define NB_MONSTER 16


typedef struct Arcs Arcs;
typedef struct Graph Graph;

struct Arcs 
{
  int u;  //sommet1
  int v;  //sommet2
  int w;  //weight
};

struct Graph 
{
  Arcs *arrayArcs;  
};






