#include "/home/trx/INFO2A/PROJET/S2/level1/src/graph2.c"
#include "/home/trx/INFO2A/PROJET/S2/level1/include/display.h"

int main() {
	
	Graph* graph = jsonCreateGraphFromFile("/home/trx/INFO2A/PROJET/S2/level1/ressources/graph.json");
	displayGraphWindow(graph);
	return 0;
}