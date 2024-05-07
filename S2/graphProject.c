
#include "graphLevel1.h"

Graph *structReadFirstGraph()
{
    Graph *myGraph = (Graph*)malloc(sizeof(Graph));

    FILE *myFile = fopen("graphTPpt1.txt", "r");
    int iTopI = 0;
    int iTopJ = 0;
    int iType = 0;

    if ( myFile == NULL )
    {
        exit(EXIT_FAILURE);
    }

    fscanf(myFile, "%d", &myGraph->vertex);
    printf("%d\n", myGraph->vertex);
    myGraph->adjency = (Monster**)malloc(myGraph->vertex * sizeof(Monster*));

    for ( int i = 0; i < myGraph->vertex + 1; i++)
    {
        myGraph->adjency[i] = (Monster*)malloc(myGraph->vertex * sizeof(Monster));

        for ( int j = 0; j < myGraph->vertex + 1; j++)
        {
            myGraph->adjency[i][j].monsterType = 0;
        }
    }

    while( fscanf(myFile,"%d %d %d", &iTopI,&iTopJ,&iType) == 3)
    {
        myGraph->adjency[iTopI][iTopJ].monsterType = iType;
        myGraph->adjency[iTopI][iTopJ].vertex = iTopI;
    }

    fclose(myFile);
    
    return myGraph;
}


void showAdjencyMatrix( int vertex, int **myGraph)
{
    printf("-----------------  MATRIX  ----------------\n");
    for ( int i = 1; i <= vertex; i++)
    {
        for ( int j = 1; j <= vertex; j++)
        {
            printf("%d ", myGraph[i][j]);
        }
        printf("\n");
    }
}
