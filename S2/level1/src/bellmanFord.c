#include "/home/trx/INFO2A/PROJET/S2/level1/include/graph.h"


void BellmanFord(Graph *graph, int source) {
    //variables
    int i, j, u, v, w;

    //total vertex in the graph g
    int tV = graph->order;

    //total edge in the graph g
    int tE = graph->nbArcs;

    //distance array
    //size equal to the number of vertices of the graph g
    int* d = malloc((tV) * sizeof(int));

    //predecessor array
    //size equal to the number of vertices of the graph g
    int* p = malloc((tV) * sizeof(int));

    //step 1: fill the distance array and predecessor array
    for (i = 0; i < tV; i++) {
        d[i] = INT_MAX;
        p[i] = 0;
    }

    //mark the source vertex
    d[source] = 0;

    //step 2: relax edges |V| - 1 times
    for (i = 1; i <= tV - 1; i++) {
        for (j = 0; j < tE; j++) {
            //get the edge data
            u = graph->arcs[j].sommet1;
            v = graph->arcs[j].sommet2;
            w = graph->arcs[j].weight;

            if (d[u] != INT_MAX && d[v] > d[u] + w) {
                d[v] = d[u] + w;
              /*  printf("w = %d, ", w);
                printf("d[%d] = %d, ", u, d[u]);
                printf("d[%d] = %d\n", v, d[v]);*/
                p[v] = u;
            }
        }
    }

}