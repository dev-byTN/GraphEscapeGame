#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#include "dijkstra.h"

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
        printf("Impossible d'ouvrir le fichier graphe.txt\n");
        return NULL;
    }
    int order;
    fscanf(file, "%d", &order);
    //  printf("Order: %d\n", order);
    Graphe *graphe = malloc(sizeof(Graphe));
    graphe->order = order;
    graphe->arcs = malloc(graphe->order * graphe->order * sizeof(Arc));
    int *buffer = malloc(3 * sizeof(int));

    while (fscanf(file, "%d %d %d", &buffer[0], &buffer[1], &buffer[2]) != EOF) {
        // printf("Arc: %d -> %d\n", buffer[0], buffer[1]);
        Arc *arc = malloc(sizeof(Arc));
        arc->sommet1 = buffer[0] - 1;
        arc->sommet2 = buffer[1] - 1;
        arc->weight = buffer[2];
        arc->color = -1;

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
                successor->sommet = j;
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
            printf("%d ", successor->sommet + 1);
            successor = successor->nextSuccessor;
        }
        printf("\n");
    }
}


int main() {
    FILE *file = fopen("monsterLevel1.txt", "r");
    Graphe *graphe = lectureGraphe(file);
    printf("Matrice d'adjacence: \n");
    //afficheMatrice(graphe);

    printf("\n Successeurs: \n");
    ListSuccessor **successors = getSuccessorList(graphe);
    //afficheSuccessors(graphe->order, successors);

    dijkstra(graphe, 0);
    BellmanFord(graphe, 0);

    edgeColoration(graphe, 0);

    /*printf("\n Successeurs: \n");
    showSuccessors(graphe, adjacence);
    printf("\n PrÃ©decesseurs: \n");
    showPredecessors(graphe, adjacence);
    printf("\n Arcs: \n");
    showArcs(graphe);
    printf("\n Nombre de chemins de longueur 2: %d\n", nbchemin2(graphe->order, adjacence));*/

    for (int i = 0; i < graphe->order; ++i) {
        free(graphe->adjency[i]);
        freeList(successors[i]);
    }

    free(graphe->adjency);
    free(graphe);
    free(successors);
    return 0;
}