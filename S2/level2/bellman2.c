#include "./bellmanFord.h"

void displayPredecessor(int tv, int predecessor[]){
    for ( int i = 0; i < tv; i++){
        printf("%d -> ", predecessor[i]);
    }
    printf("\n");
}


int bellmanford2(Graph *monster, int start, int end)   
{
    int u, v, w;
    int tv = monster->V;
    int te = monster->E;

    int distance[tv];
    int predecessor[tv];

    for (int i = 0; i < tv; i++) 
    {
        distance[i] = INT_MIN;
        predecessor[i] = 0;
    }
    distance[start] = 0;

    for (int i = 0; i < tv; i++) 
    {
        for (int j = 0; j < tv; j++) 
        {
            u = monster->arrayArcs[j].u; // SOMMET DE DÉPART
            v = monster->arrayArcs[j].v; // SOMMET D'ARRIVÉ
            w = monster->arrayArcs[j].w; // POIDS

            if (distance[u] != INT_MIN && (distance[v] < distance[u] + w)) 
            {
                distance[v] = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }
    displayPredecessor(tv,predecessor);

    return distance[end];
}


