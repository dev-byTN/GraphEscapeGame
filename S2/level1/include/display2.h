#pragma once
#include "graphh.h"
#include "raylib.h"

void displayGraphWindow(Graphe* graph);

void drawGraph(int show, Rectangle* textBox,
	char* name, int letterCount, int framesCounter,
	Vector2* currentPoint, Vector2* startPoint,
	Graphe* graph, int moveStartPoint, Arc* movingNode, int pressed,
	Vector2* mouse, int* createEdge);

void drawEdgeWeightEditBox(int show, Rectangle* textBox, char* edgeWeight, int letterCount, int framesCounter);
void drawOrientedCurve(Arc* node, ListSuccessor* adjencyList, Vector2* middle);