#include "graph.c"
#include "bellmanFord.c"
#include "dijkstra.c"


int **getWeightedAdjency(Graph *graphe) {
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

Graph *lectureGraphe(FILE *file) {
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }
    int order;
    fscanf(file, "%d", &order);
    //  printf("Order: %d\n", order);
    Graph *graphe = malloc(sizeof(Graph));
    graphe->order = order;
    graphe->arcs = malloc(graphe->order * graphe->order * sizeof(Arc));
    int *buffer = malloc(3 * sizeof(int));

    while (fscanf(file, "%d %d %d", &buffer[0], &buffer[1], &buffer[2]) != EOF) {
        // printf("Arc: %d -> %d\n", buffer[0], buffer[1]);
        Arc *arc = malloc(sizeof(Arc));
        arc->sommet1 = buffer[0] - 1;
        arc->sommet2 = buffer[1] - 1;
        arc->weight = buffer[2];

        graphe->arcs[graphe->nbArcs] = *arc;
        graphe->nbArcs++;
    }
    graphe->adjency = getWeightedAdjency(graphe);

    fclose(file);
    return graphe;
}

ListSuccessor **getSuccessorList(Graph *graph) {
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

void afficheMatrice(Graph *graph) {
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


////////////////////////////// JSON PART /////////////////////////////////



