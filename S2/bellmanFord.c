#include "bellmanFord.h"


int bellmanford(Graph *monster, int start, int end)   
{
    int u, v, w;
    int tv = monster->V;
    int te = monster->E;
    int count = 0;

    int distance[tv];
    int predecessor[tv];

    for (int i = 0; i < tv; i++) 
    {
        distance[i] = INT_MAX;
        predecessor[i] = 0;
    }
    distance[start] = 0;

    for (int i = 1; i <= tv - 1; i++) 
    {
        for (int j = 0; j < te; j++) 
        {
            u = monster->arrayArcs[j].u; // SOMMET DE DÉPART
            v = monster->arrayArcs[j].v; // SOMMET D'ARRIVÉ
            w = monster->arrayArcs[j].w; // POIDS

            if (distance[u] != INT_MAX && (distance[v] > distance[u] + w)) 
            {
                distance[v] = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }

    return distance[end];
}


