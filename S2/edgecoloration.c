#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void coloration(Graphe *graph, int *colors, Arc arc) {
    Arc *arcs = graph->arcs;
    Arc *adjacentArcs = malloc(graph->order * sizeof(Arc));
    int adjacentArcsSize = 0;

    for (int i = 0; i < graph->nbArcs; ++i) {
        if (&arcs[i] == &arc || arcs[i].color != -1) {
            continue;
        }
        if (arcs[i].sommet1 == arc.sommet1 || arcs[i].sommet1 == arc.sommet2 || arcs[i].sommet2 == arc.sommet1 ||
            arcs[i].sommet2 == arc.sommet2) {
            adjacentArcs[adjacentArcsSize] = arcs[i];
            adjacentArcsSize++;
        }
    }

    printf("Adjacent arcs size: %d\n", adjacentArcsSize);

    int* usedColors = malloc(graph->order * sizeof(int));

    for (int i = 0; i < adjacentArcsSize; ++i) {
        usedColors[i] = -1;
    }
    usedColors[arc.color] = 1;

    for (int i = 0; i < adjacentArcsSize; ++i) {
        Arc adjacentArc = adjacentArcs[i];
        if (adjacentArc.color != -1) {
            usedColors[adjacentArc.color] = 1;
        }
    }

    free(adjacentArcs);
    free(usedColors);
}

int *edgeColoration(Graphe *graph, int source) {
    Arc *arcs = graph->arcs;
    int *colors = malloc((graph->order + 1) * sizeof(int));

    for (int i = 0; i < graph->order; i++) {
        colors[i] = i;
    }
    arcs[source].color = 0;

    coloration(graph, colors, arcs[source]);
}