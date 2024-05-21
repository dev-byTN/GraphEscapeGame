#include "./bellmanFord.h"

void displayPredecessor(int tv, int predecessor[]){
    for ( int i = 0; i < tv; i++){
        printf("%d -> ", predecessor[i]);
    }
    printf("\n");
}


int bellmanford2(Graph *graph, int start, int end)   
{
    int u, v, w;
    int tV = graph->order;
    int tE = graph->nbArcs;

    int *distance = malloc((tV) * sizeof(int));
    int *predecessor = malloc((tV) * sizeof(int));

    for (int i = 0; i < tV; i++) 
    {
        distance[i] = INT_MIN;
        predecessor[i] = 0;
    }
    distance[start] = 0;

    for (int i = 0; i < tV; i++) 
    {
        for (int j = 0; j < tV; j++) 
        {
            u = graph->arcs[j].sommet1; 
            v = graph->arcs[j].sommet2; 
            w = graph->arcs[j].weight; 

            if (distance[u] != INT_MIN && (distance[v] < distance[u] + w)) 
            {
                distance[v] = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }
    //displayPredecessor(tv,predecessor);

    return distance[end];
}


