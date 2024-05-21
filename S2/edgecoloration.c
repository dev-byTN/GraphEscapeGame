#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

    int *usedColors = malloc(graph->order * sizeof(int));

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

bool isAlreadyAdded(Arc arc, ListSuccessor *list) {
    Successor *current = list->firstSuccessor;
    while (current != NULL) {
        Arc *currentArc = current->element;
        if (currentArc->id != arc.id && (arc.sommet1 == currentArc->sommet2 && arc.sommet2 == currentArc->sommet1)) {
           // printf("Arc %d -> %d already added\n", arc.sommet1, arc.sommet2);
            return true;
        }
        current = current->nextSuccessor;
    }
    return false;
}


ListSuccessor *adjacentArcs(Arc *arcs, int nbArcs, Arc arc) {
    ListSuccessor *adjacentArcsList = createList();

    for (int i = 0; i < nbArcs; ++i) {
        if (arcs[i].id == arc.id) {
            continue;
        }
        if ((arcs[i].sommet1 == arc.sommet1 || arcs[i].sommet1 == arc.sommet2 || arcs[i].sommet2 == arc.sommet1 ||
             arcs[i].sommet2 == arc.sommet2) && !isAlreadyAdded(arcs[i], adjacentArcsList)) {
            Successor *successor = malloc(sizeof(Successor));
            successor->element = &arcs[i];
            successor->nextSuccessor = NULL;

            insertElement(adjacentArcsList, successor);
        }
    }
   // printf("Adjacent arcs size: %d\n", adjacentArcsList->size);
    return adjacentArcsList;
}

void edgeColoration(Graphe *graph, int source) {
    Arc *arcs = graph->arcs;
    int *colors = malloc((graph->order + 1) * sizeof(int));

    int markedArcs = 0;
    int currentArc = 0;

    while (markedArcs < graph->nbArcs) {
        Arc arc = arcs[currentArc];

        if (arc.color != -1) {
            currentArc++;
            continue;
        }
        ListSuccessor *adjacentArcsList = adjacentArcs(arcs, graph->nbArcs, arc);
        ListSuccessor *usedColorsList = createList();

        printf("Adjacent arcs of %d -> %d: \n", arc.sommet1 + 1, arc.sommet2 + 1);

        Successor *current = adjacentArcsList->firstSuccessor;

        while (current != NULL) {
            Arc *currentArc = current->element;

            printf("Color of %d -> %d: %d\n", currentArc->sommet1 + 1, currentArc->sommet2 + 1, currentArc->color);

            if (currentArc->color != -1) {
                Successor *colorSuccessor = malloc(sizeof(Successor));
                colorSuccessor->element = currentArc->color;
                colorSuccessor->nextSuccessor = NULL;

                insertElement(usedColorsList, colorSuccessor);
              //  printf("Inserted color %d\n", currentArc->color);
            }

            printf("%d -> %d \n", currentArc->sommet1 + 1, currentArc->sommet2 + 1);
            current = current->nextSuccessor;
        }
        int color = 0;

        for (int i = 0; i < 5; ++i) {
            Successor *currentArc = usedColorsList->firstSuccessor;
            bool used = false;

            while (currentArc != NULL) {
                int currentColor =currentArc->element;

              //  printf("Color: %d\n", currentColor);

                if (currentColor == i) {
                    used = true;
                    break;
                }
                currentArc = currentArc->nextSuccessor;
            }

            if (!used) {
                color = i;
                break;
            }
        }
        arc.color = color;
        markedArcs++;
        currentArc++;
        printf("Setted color of %d -> %d: %d\n", arc.sommet1 + 1, arc.sommet2 + 1, arc.color);
       // printf("Color of %d -> %d: %d\n", arc.sommet1 + 1, arc.sommet2 + 1, arc.color);

    }
}