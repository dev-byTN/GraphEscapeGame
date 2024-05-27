#include "include/edgecoloration.h"

bool isAlreadyAdded(Arc *arc, ListSuccessor *list) {
    Successor *current = list->firstSuccessor;
    while (current != NULL) {
        Arc *currentArc = current->element;
        if (currentArc->id != arc->id && (arc->sommet1 == currentArc->sommet2 && arc->sommet2 == currentArc->sommet1)) {
            // printf("Arc %d -> %d already added\n", arc.sommet1, arc.sommet2);
            return true;
        }
        current = current->nextSuccessor;
    }
    return false;
}

ListSuccessor *getOneWayArcsList(ListSuccessor *arcsList) {
    ListSuccessor *oneWayArcsList = createList();
    Successor *current = arcsList->firstSuccessor;

    while (current != NULL) {
        Arc *arc = current->element;
        if (!isAlreadyAdded(arc, oneWayArcsList)) {
            Successor *successor = malloc(sizeof(Successor));
            successor->element = arc;
            successor->nextSuccessor = NULL;

            insertElement(oneWayArcsList, successor);
        }
        current = current->nextSuccessor;
    }

    return oneWayArcsList;
}

ListSuccessor *getAdjacentArcs(ListSuccessor *arcsList, Arc *arc) {
    ListSuccessor *adjacentArcsList = createList();
    Successor *current = arcsList->firstSuccessor;

    while (current != NULL) {
        Arc *currentArc = current->element;
        if (currentArc->id == arc->id) {
            current = current->nextSuccessor;
            continue;
        }
        if ((currentArc->sommet1 == arc->sommet1 || currentArc->sommet1 == arc->sommet2 ||
             currentArc->sommet2 == arc->sommet1 || currentArc->sommet2 == arc->sommet2)) {
            Successor *successor = malloc(sizeof(Successor));
            successor->element = currentArc;
            successor->nextSuccessor = NULL;

            insertElement(adjacentArcsList, successor);
        }
        current = current->nextSuccessor;
    }
    // printf("Adjacent arcs size: %d\n", adjacentArcsList->size);
    return adjacentArcsList;
}

char* getColorFromIntValue(int value) {
    switch (value) {
        case 0:
            return "Red";
        case 1:
            return "Green";
        case 2:
            return "Blue";
        case 3:
            return "Yellow";
        case 4:
            return "Purple";
        default:
            return "No defined";
    }

}

int edgeColoration(Graphe *graph, int source) {
    ListSuccessor *arcsList = getOneWayArcsList(graph->arcsList);
    Successor *currentArcList = arcsList->firstSuccessor;

    int markedArcs = 0;
    int colorsUsed = 0;

    while (markedArcs < graph->nbArcs && currentArcList != NULL) {
        Arc *arc = (Arc *) currentArcList->element;

        if (arc->color != -1) {
            currentArcList = currentArcList->nextSuccessor;
            continue;
        }
        ListSuccessor *adjacentArcsList = getAdjacentArcs(arcsList, arc);
        ListSuccessor *usedColorsList = createList();

        Successor *current = adjacentArcsList->firstSuccessor;

        while (current != NULL) {
            Arc *currentArc = current->element;

            if (currentArc->color != -1) {
                Successor *colorSuccessor = malloc(sizeof(Successor));
                int *color = malloc(sizeof(int));
                *color = currentArc->color;

                colorSuccessor->element = color;
                colorSuccessor->nextSuccessor = NULL;

                insertElement(usedColorsList, colorSuccessor);
            }

            current = current->nextSuccessor;
        }
        int color = 0;

        // 5 beceause we are in a labyrinth (mathematics hypothesis says that max colors used is (max(order(G)) = 4) + 1
        for (int i = 0; i < 5; ++i) {
            Successor *currentArc = usedColorsList->firstSuccessor;
            bool used = false;

            while (currentArc != NULL) {
                int *currentColor = currentArc->element;

                if (*currentColor == i) {
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
        arc->color = color;

        if (color > colorsUsed) {
            colorsUsed = color;
        }
        markedArcs++;
        currentArcList = currentArcList->nextSuccessor;
         printf("Color of edge (%d -> %d): %s\n", arc->sommet1 + 1, arc->sommet2 + 1, getColorFromIntValue(arc->color));
    }
    return colorsUsed + 1;
}