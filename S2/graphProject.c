#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "include/graph.h"
#include "include/dijkstra.h"
#include "include/edgeColoration.h"

int **getWeightedAdjency(Graphe *graphe) {
    int **adjacence = malloc(graphe->order * sizeof(int *));


    for (int i = 0; i < graphe->order; ++i) {
        adjacence[i] = malloc(graphe->order * sizeof(int));
    }


    for (int i = 0; i < graphe->order; ++i) {
        for (int j = 0; j < graphe->order; ++j) {
            adjacence[i][j] = 0;
        }
    }

    for (int i = 0; i < graphe->nbArcs; ++i) {
        Arc arc = graphe->arcs[i];
        adjacence[arc.sommet1][arc.sommet2] = arc.weight;
    }
    return adjacence;
}

Graphe *lectureGraphe(FILE *file) {
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return NULL;
    }
    int order;
    fscanf(file, "%d", &order);
    //  printf("Order: %d\n", order);
    Graphe *graphe = malloc(sizeof(Graphe));
    graphe->order = order;
    graphe->arcs = malloc(graphe->order * graphe->order * sizeof(Arc));
    graphe->arcsList = createList();
    graphe->nbArcs = 0;

    printf("List created\n");

    int *buffer = malloc(3 * sizeof(int));
    int id = 0;

    while (fscanf(file, "%d %d %d", &buffer[0], &buffer[1], &buffer[2]) != EOF) {
        // printf("Arc: %d -> %d\n", buffer[0], buffer[1]);
        Arc *arc = malloc(sizeof(Arc));
        arc->sommet1 = buffer[0] - 1;
        arc->sommet2 = buffer[1] - 1;
        arc->weight = buffer[2];
        arc->color = -1;
        arc->id = id;

        Successor *arcElement = malloc(sizeof(Successor));

        if (arcElement == NULL) {
            printf("Error while allocating memory\n");
            return NULL;
        }

        arcElement->element = arc;
        arcElement->nextSuccessor = NULL;

        insertElement(graphe->arcsList, arcElement);
        id++;

        graphe->arcs[graphe->nbArcs] = *arc;
        graphe->nbArcs++;
    }
    graphe->adjency = getWeightedAdjency(graphe);

    fclose(file);
    return graphe;
}

ListSuccessor **getSuccessorList(Graphe *graph) {
    ListSuccessor **successors = malloc(graph->order * sizeof(ListSuccessor *));

    for (int i = 0; i < graph->order; i++) {
        successors[i] = createList();
    }

    for (int i = 0; i < graph->order; i++) {
        for (int j = 0; j < graph->order; j++) {

            if (graph->adjency[i][j] != 0) {
                Successor *successor = malloc(sizeof(Successor));
                int *value = malloc(sizeof(int));
                *value = j;

                successor->element = value;
                successor->nextSuccessor = NULL;
                insertElement(successors[i], successor);
            }
        }
    }
    return successors;
}

void afficheMatrice(Graphe *graph) {
    for (int i = 0; i < graph->order; i++) {
        for (int j = 0; j < graph->order; j++) {
            printf("%d ", graph->adjency[i][j]);
        }
        printf("\n");
    }
}

void afficheSuccessors(int order, ListSuccessor **successors) {
    for (int i = 0; i < order; i++) {
        printf("Successeurs de %d: ", i + 1);
        Successor *successor = successors[i]->firstSuccessor;
        while (successor != NULL) {
            int *value = successor->element;
            printf("%d ", *value + 1);
            successor = successor->nextSuccessor;
        }
        printf("\n");
    }
}

void resetEdges(Graphe *graph) {
    ListSuccessor *arcsList = graph->arcsList;
    Successor *currentArcList = arcsList->firstSuccessor;

    while (currentArcList != NULL) {
        Arc *arc = (Arc *) currentArcList->element;
        arc->color = -1;
        currentArcList = currentArcList->nextSuccessor;
    }
}
