#include "graphProject.c"

int main()
{
    FILE *file = fopen("/home/trx/INFO2A/PROJET/S2/level1/ressources/monsterLevel1.txt", "r");
    Graph *graph = lectureGraphe(file);
    //printf("Matrice d'adjacence: \n");
    //afficheMatrice(graphe);

    printf("\n Successeurs: \n");
    ListSuccessor **successors = getSuccessorList(graph);
    afficheSuccessors(graph->order, successors);

    //dijkstra(graph, 0);
    //BellmanFord(graph, 0);


}
