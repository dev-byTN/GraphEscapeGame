#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"
#include "dijkstra.h"

int **getWeightedAdjacence(Graphe *graphe) {
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
        adjacence[arc.sommet1 - 1][arc.sommet2 - 1] = arc.weight;
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
        arc->sommet1 = buffer[0];
        arc->sommet2 = buffer[1];
        arc->weight = buffer[2];

        graphe->arcs[graphe->nbArcs] = *arc;
        graphe->nbArcs++;
    }

    fclose(file);
    return graphe;
}

ListSuccessor **getSuccessorList(int **adjacence, int order) {
    ListSuccessor **successors = malloc(order * sizeof(ListSuccessor * ));

    for (int i = 0; i < order; i++) {
        successors[i] = createList();
    }

    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {

            if (adjacence[i][j] != 0) {
                Successor *successor = malloc(sizeof(Successor));
                successor->sommet = j;
                successor->nextSuccessor = NULL;
                insertElement(successors[i], successor);
            }
        }
    }
    return successors;
}

void afficheMatrice(int ordre, int **adjacence) {
    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            printf("%d ", adjacence[i][j]);
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
    int **weightedAdjacence = getWeightedAdjacence(graphe);
    printf("Matrice d'adjacence: \n");
    afficheMatrice(graphe->order, weightedAdjacence);

    printf("\n Successeurs: \n");
    ListSuccessor **successors = getSuccessorList(weightedAdjacence, graphe->order);
    //afficheSuccessors(graphe->order, successors);

    dijkstra(weightedAdjacence, graphe->order, 0);

    /*printf("\n Successeurs: \n");
    showSuccessors(graphe, adjacence);
    printf("\n PrÃ©decesseurs: \n");
    showPredecessors(graphe, adjacence);
    printf("\n Arcs: \n");
    showArcs(graphe);
    printf("\n Nombre de chemins de longueur 2: %d\n", nbchemin2(graphe->order, adjacence));*/

    for (int i = 0; i < graphe->order; ++i) {
        free(weightedAdjacence[i]);
        freeList(successors[i]);
    }

    free(weightedAdjacence);
    free(graphe);
    free(successors);
    return 0;
}