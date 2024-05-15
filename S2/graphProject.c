#include "graphLevel1.h"


ListMonster* newListVertex()
{
    ListMonster* newList = (ListMonster*)malloc(sizeof(ListMonster));
    if(newList == NULL)
    {
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;

    return newList;
}


int addVertex(ListMonster* list, int start, int end, int weight) 
{
    Graph *newMonster = (Graph*)malloc(sizeof(Graph));
    newMonster->arrayArc = (Arc*)malloc(NB_EDGE * sizeof(Arc));

    if (newMonster == NULL || list == NULL) 
    {
        exit(EXIT_FAILURE);
    }

    newMonster->arrayArc->u = start;
    newMonster->arrayArc->v = end;
    newMonster->arrayArc->w = weight;

    newMonster->next = list->head;
    list->head = newMonster;

    return 0;
}


Graph *readGraphLevel1()
{
    Graph *myGraph = (Graph*)malloc(sizeof(Graph));

    FILE *myFile = fopen("monsterLevel1.txt", "r");
    int iTopI = 0;
    int iTopJ = 0;
    int iType = 0;
    int iVertice = 0;

    if ( myFile == NULL )
    {
        exit(EXIT_FAILURE);
    }

    fscanf(myFile, "%d", &iVertice);
    myGraph->adjency = (int**)malloc(NB_MONSTER * sizeof(int*));

    for ( int i = 1; i <= NB_MONSTER; i++)
    {
        myGraph->adjency[i] = (int*)malloc(NB_MONSTER * sizeof(int));

        for ( int j = 1; j <= NB_MONSTER; j++)
        {
            myGraph->adjency[i][j] = 0;
        }
    }

    myGraph->arrayArc = (Arc*)malloc(NB_EDGE * sizeof(Arc));
    while( fscanf(myFile,"%d %d %d", &iTopI,&iTopJ,&iType) == 3)
    {
        myGraph->adjency[iTopI][iTopJ] = iType;
        myGraph->arrayArc->u = iTopI;
        myGraph->arrayArc->v = iTopJ;
        myGraph->arrayArc->w = iType;
    }

    fclose(myFile);
    
    return myGraph;
}


void adjencyMatrixLevel1(Graph *myGraph)
{
    printf("-----------------  MATRIX  ----------------\n");
    for ( int i = 1; i <= NB_MONSTER; i++)
    {
        for ( int j = 1; j <= NB_MONSTER; j++)
        {
            printf("%d ", myGraph->adjency[i][j]);
        }
        printf("\n");
    }
}


ListMonster** creationListMonster(Graph* myGraph)
{
    ListMonster** list = (ListMonster**)malloc(NB_MONSTER * sizeof(ListMonster*));
    if (list == NULL) 
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= NB_MONSTER; i++) 
    {
        list[i] = newListVertex();
        if (list[i] == NULL) 
        {
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= NB_MONSTER; i++) 
    {
        for (int j = 1; j <= NB_MONSTER; j++) 
        {
            if (myGraph->adjency[i][j] != 0) 
            {
                addVertex(list[i], i, j, myGraph->arrayArc[i].w);
                //printf("%d(%d) ", myGraph->arrayArc->v, myGraph->arrayArc->w);
            }
        }
    }

    return list;
}


void displayVertexList(ListMonster** list) 
{
    for (int i = 1; i <= NB_MONSTER ; i++) 
    {
        
        printf("Vertex of %d : ", i);
        Graph* current = list[i]->head;
        current->arrayArc = (Arc*)malloc(NB_EDGE * sizeof(Arc));
        while (current != NULL) 
        {
            printf("%d(%d) ", current->arrayArc[i].v, current->arrayArc[i].w);
            current = current->next;
        }
        printf("\n");
    }
}

int bellmanford(Graph *monster, int start, int end) 
{
    int u, v, w;
    int totalV = monster->tv;
    int totalE = monster->te;

    int distance[NB_MONSTER];
    int predecessor[NB_MONSTER];

    for (int i = 0; i < NB_MONSTER; i++) 
    {
        distance[i] = INT_MAX;
        predecessor[i] = 0;
    }
    distance[start] = 0;

    for (int i = 1; i <= NB_MONSTER - 1; i++) 
    {
        for (int j = 0; j < NB_EDGE; j++) 
        {
            u = monster->arrayArc[i].u; // SOMMET DE DÉPART
            v = monster->arrayArc[i].v; // SOMMET D'ARRIVÉ
            w = monster->arrayArc[i].w; // POIDS

            if (distance[u] != INT_MAX && (distance[v] > distance[u] + w)) 
            {
                distance[v] = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }

    return distance[end];
}

