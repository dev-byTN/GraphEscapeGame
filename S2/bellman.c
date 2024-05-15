#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 1; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// The main function that finds shortest distances from src
// to all other vertices using Bellman-Ford algorithm.  The
// function also detects negative weight cycle
void BellmanFord(Graphe* graph, int src)
{
    int V = graph->order;
    int E = graph->nbArcs;
    int* dist = malloc(V * sizeof(int));

    // Step 1: Initialize distances from src to all other
    // vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at-most |V| - 1 edges
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->arcs[j].sommet1;
            int v = graph->arcs[j].sommet2;
            int weight = graph->arcs[j].weight;


            if (dist[u] != INT_MAX && (dist[u] + weight < dist[v])) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: check for negative-weight cycles.  The above
    // step guarantees shortest distances if graph doesn't
    // contain negative weight cycle.  If we get a shorter
    // path, then there is a cycle.
    for (int i = 0; i < E; i++) {
        int u = graph->arcs[i].sommet1;
        int v = graph->arcs[i].sommet2;
        int weight = graph->arcs[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle");
            return; // If negative cycle is detected, simply
            // return
        }
    }

    printArr(dist, V);

    return;
}