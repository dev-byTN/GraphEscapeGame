#pragma once
#include "graph.h"
#include "raylib.h"

void displayGraphWindow(Graph* graph);

void prepareGraphToDraw(Graph* graph, Vector2 startPoint,
	int* pressed, int* show, Rectangle* textBox,
	int* letterCount, char* edgeWeight, NodesList** editedEges, int* framesCounter, int* creatingNode,
	Node** movingNode, Vector2* mouse, int* createEdge);


void drawGraph(int show, Rectangle* textBox,
	char* name, int letterCount, int framesCounter,
	Vector2* currentPoint, Vector2* startPoint,
	Graph* graph, int moveStartPoint, Node* movingNode, int pressed,
	Vector2* mouse, int* createEdge);

void drawEdgeWeightEditBox(int show, Rectangle* textBox, char* edgeWeight, int letterCount, int framesCounter);
void drawOrientedCurve(Node* node, NodesList* adjencyList, Vector2* middle);
