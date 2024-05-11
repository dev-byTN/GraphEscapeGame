#include "graphLevel1.h"


ListMonster* newListVertex ()
{
    ListMonster* newList = (ListMonster*)malloc(sizeof(ListMonster));
    if(newList == NULL)
    {
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;
    newList->nbVertex = 0;

    return newList;
}


int addVertex(ListMonster* list, int vertex) 
{
    Monster* vertexTemp = (Monster*)malloc(sizeof(Monster));
    if (vertexTemp != NULL) 
    {
        vertexTemp->nextvertex = vertex;
        vertexTemp->next = list->head;
        list->head = vertexTemp;
        list->nbVertex +=1;
    }

    return 0;
}


Monster *readGraphLevel1()
{
    Monster *myGraph = (Monster*)malloc(sizeof(Monster));

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

    for ( int i = 0; i < NB_MONSTER + 1; i++)
    {
        myGraph->adjency[i] = (int*)malloc(NB_MONSTER * sizeof(int));

        for ( int j = 0; j < NB_MONSTER + 1; j++)
        {
            myGraph->adjency[i][j] = 0;
        }
    }

    while( fscanf(myFile,"%d %d %d", &iTopI,&iTopJ,&iType) == 3)
    {
        myGraph->adjency[iTopI][iTopJ] = iType;
        myGraph->monsterType = iType;
        myGraph->nextvertex = iTopJ;
    }

    fclose(myFile);
    
    return myGraph;
}


void adjencyMatrixLevel1( Monster *myGraph)
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


ListMonster** creationListMonster(Monster* myGraph)
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
                addVertex(list[i], j);
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
        Monster* current = list[i]->head;
        while (current != NULL) 
        {
            printf("%d(%d) ", current->nextvertex, current->monsterType);
            current = current->next;
        }
        printf("\n");
    }
}
