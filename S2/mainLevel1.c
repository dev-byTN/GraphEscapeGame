#include "graphProject.c"

int main()
{
    int vertice = 0;
    int **myGraph = readGraph(vertice);

    showAdjencyMatrix(vertice, myGraph);
}
