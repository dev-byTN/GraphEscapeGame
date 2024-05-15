#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
  int V;
  int E;
};






