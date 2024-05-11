#include "graph.h"

void bellmanford(int source, Monster *monster) 
{
    int u, v, w;

    int distance[NB_MONSTER];
    int predecessor[NB_EDGE];

    for (int i = 0; i < NB_MONSTER; i++) 
    {
        distance[i] = INT_MAX;
        predecessor[i] = 0;
    }
    distance[source] = 0;

    for (int i = 1; i <= NB_MONSTER - 1; i++) 
    {
        for (int j = 0; j < NB_EDGE; j++) 
        {
            u = monster->adjency[i][j].u; // SOMMET DE DÉPART
            v = monster->adjency[i][j].v; // SOMMET D'ARRIVÉ
            w = myGraph->adjecny[i][j].w; // POIDS

            if (distance[u] != INT_MAX && (distance[v] > distance[u] + w)) 
            {
                distance[v] = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }

    printf("Distance array: ");
    display(distance, NB_MONSTER);
    printf("Predecessor array: ");
    display(predecessor, NB_MONSTER);
}
