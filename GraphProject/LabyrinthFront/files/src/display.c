#include "../include/display.h"

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_CHARS     3

//Function to display the graph in a window
void displayGraphWindow(Graph* graph)
{

	//Arbitrary starting point in the upper left corner of the window
	Vector2 startPoint = { 100, 100 };

	//Variable needed for moving nodes and creating edges
	Node* movingNode = NULL;
	int moveStartPoint = -1;
	int pressed = 0;

	int createEdge = 0;

	int displayEdgeWeightEditBox = 0;

	//Variables for text input
	char editedText[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 0, 0, 120, 50 };

	int framesCounter = 0; //Variable for the blinking underscore


	Vector2 currentPoint = startPoint;
	Vector2 mouse;

		currentPoint = startPoint;
		mouse = GetMousePosition();

		//Get all information needed to draw the graph
		//such user inputs, moving nodes, creating edges, etc.

		drawGraph(displayEdgeWeightEditBox, &textBox,
			editedText, letterCount, framesCounter, &currentPoint, &startPoint,
			graph, moveStartPoint, movingNode, pressed,
			&mouse, &createEdge);

}



void drawGraph(int showEdgeWeightEditBox, Rectangle* textBox,
	char* edgeWeight, int letterCount, int framesCounter,
	Vector2* currentPoint, Vector2* startPoint,
	Graph* graph, int moveStartPoint, Node* movingNode, int pressed,
	Vector2* mouse, int* createEdge)
{


	currentPoint = startPoint;
	int line = 0;
	int column = 0;
	NodesList* graphNodes = graph->nodes;
	while (graphNodes->next != NULL)
	{
		Node* node = graphNodes->node;
		if (node->x == -1 && node->y == -1)
		{
			node->x = currentPoint->x;
			node->y = currentPoint->y;
		}
		else
		{
			currentPoint->x = node->x;
			currentPoint->y = node->y;
		}
		NodesList* adjencyList = node->adjacent;
		while (adjencyList != NULL && adjencyList->node != NULL)
		{
			Vector2 middle = Vector2Add((Vector2) { node->x, node->y }, (Vector2) { adjencyList->node->x, adjencyList->node->y });
			middle = Vector2Scale(middle, 0.5);
			if (!graph->oriented)
				DrawLine((int)node->x, (int)node->y, (int)adjencyList->node->x, (int)adjencyList->node->y, GREEN);
			else
				drawOrientedCurve(node, adjencyList, &middle);

			DrawText(TextFormat("%d", adjencyList->weight), (int)middle.x, (int)middle.y, 25, WHITE);

			adjencyList = adjencyList->next;
		}


		column = (column + 1) % 5;
		if (column == 0)
			line++;
		node->x = currentPoint->x;
		node->y = currentPoint->y;

		currentPoint->x = startPoint->x + 200 * column;
		currentPoint->y = startPoint->y + 300 * line;


		graphNodes = graphNodes->next;
	}
	graphNodes = graph->nodes;
	while (graphNodes->next != NULL)
	{
		Node* node = graphNodes->node;

		if (node->x == -1 && node->y == -1)
		{
			node->x = currentPoint->x;
			node->y = currentPoint->y;
		}
		else
		{
			currentPoint->x = node->x;
			currentPoint->y = node->y;
		}
		DrawCircleV(*currentPoint,
			CheckCollisionPointCircle(*mouse, *currentPoint, 30.0f) && !IsKeyDown(KEY_LEFT_SHIFT) ? 40.f : 20.f,
			(moveStartPoint != -1 && movingNode == node) ? WHITE : BLUE);
		DrawText(TextFormat("%s", node->id), (int)currentPoint->x - 5, (int)currentPoint->y - 15, 30, WHITE);
		graphNodes = graphNodes->next;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && movingNode != NULL)
	{
		*createEdge = 1;
		DrawLineEx((Vector2) { movingNode->x, movingNode->y }, * mouse, 3, BLACK);
	}

	if (showEdgeWeightEditBox)
		drawEdgeWeightEditBox(showEdgeWeightEditBox, textBox, edgeWeight, letterCount, framesCounter);


}

void drawEdgeWeightEditBox(int show, Rectangle* textBox, char* edgeWeight, int letterCount, int framesCounter)
{
	DrawRectangleRec(*textBox, LIGHTGRAY);
	DrawRectangleLines((int)textBox->x, (int)textBox->y, (int)textBox->width, (int)textBox->height, WHITE);
	DrawText(edgeWeight, (int)textBox->x + letterCount * 5, (int)textBox->y + 8, 40, MAROON);


	if (letterCount < MAX_INPUT_CHARS)
	{
		if (framesCounter > 50) DrawText("_", (int)textBox->x + 8 + MeasureText(edgeWeight, 40), (int)textBox->y + 12, 40, MAROON);
	}
	else DrawText("Press BACKSPACE to delete chars...", (int)textBox->x, (int)textBox->y - 20, 20, GRAY);
}

void drawOrientedCurve(Node* node, NodesList* adjencyList, Vector2* middle)
{
	Vector3 start = { node->x, node->y,0 };
	Vector3 end = { adjencyList->node->x, adjencyList->node->y,0 };
	Vector3 normal = Vector3Perpendicular(Vector3Subtract(end, start));
	Vector2 normalNormalized = Vector2Normalize((Vector2) { normal.x, normal.y });

	float multiplier = 30;
	normalNormalized.x *= multiplier;
	normalNormalized.y *= multiplier;

	*middle = (Vector2){ (node->x + adjencyList->node->x) / 2 + normalNormalized.x ,
		(node->y + adjencyList->node->y) / 2 + normalNormalized.y };

	Vector2 colinear = Vector2Normalize((Vector2) {
		(adjencyList->node->x - node->x) / 2,
			(adjencyList->node->y - node->y) / 2
	});
	colinear.x *= multiplier;
	colinear.y *= multiplier;
	DrawSplineSegmentBezierCubic(
		(Vector2) {
		node->x, node->y
	},
		(Vector2) {
		node->x + normalNormalized.x, node->y + normalNormalized.y
	},
		(Vector2) {
		middle->x, middle->y
	},
		* middle,
		2,
		WHITE);
	DrawSplineSegmentBezierCubic(*middle, (Vector2) { middle->x, middle->y },
		(Vector2) {
		adjencyList->node->x + normalNormalized.x, adjencyList->node->y + normalNormalized.y
	},
		(Vector2) {
		adjencyList->node->x, adjencyList->node->y
	},
		2,
		WHITE);

	multiplier = 0.2f;
	normalNormalized.x *= multiplier;
	normalNormalized.y *= multiplier;
}




//Suppression d'un node
//Suppression d'un edge
