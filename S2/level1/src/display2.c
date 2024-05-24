#include "display2.h"

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_CHARS     3


//Function to display the graph in a window
void displayGraphWindow(Graphe* graph)
{
	// Initialization
	const int screenWidth = 670;
	const int screenHeight = 400;

	//Arbitrary starting point in the upper left corner of the window
	Vector2 startPoint = { 100, 100 };

	//Variable needed for moving nodes and creating edges
	Arc* movingNode = NULL;
	int moveStartPoint = -1;
	bool moveEndPoint = false;
	int pressed = 0;

	int createEdge = 0;
	int creatingNode = 0;

	int displayEdgeWeightEditBox = 0;

	//Variables for text input
	char editedText[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 0, 0, 120, 50 };
	bool mouseOnText = false;

	int framesCounter = 0; //Variable for the blinking underscore


	Vector2 currentPoint = startPoint;
	Vector2 mouse;

	InitWindow(screenWidth, screenHeight, "Draw graph");
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		currentPoint = startPoint;
		mouse = GetMousePosition();

		// Draw the graph
		drawGraph(displayEdgeWeightEditBox, &textBox,
			editedText, letterCount, framesCounter, &currentPoint, &startPoint,
			graph, moveStartPoint, movingNode, pressed,
			&mouse, &createEdge);

	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context

	//--------------------------------------------------------------------------------------
}


void drawGraph(int showEdgeWeightEditBox, Rectangle* textBox,
	char* edgeWeight, int letterCount, int framesCounter,
	Vector2* currentPoint, Vector2* startPoint,
	Graphe* graph, int moveStartPoint, Arc* movingNode, int pressed,
	Vector2* mouse, int* createEdge)
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	currentPoint = startPoint;
	int line = 0;
	int column = 0;
	ListSuccessor* graphNodes = graph->arcsList;
	while (graphNodes->next != NULL)
	{
		Arc* node = graphNodes->node;
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
		ListSuccessor* adjencyList = node->adjacent;
		while (adjencyList != NULL && adjencyList->node != NULL)
		{
			Vector2 middle = Vector2Add((Vector2) { node->x, node->y }, (Vector2) { adjencyList->node->x, adjencyList->node->y });
			middle = Vector2Scale(middle, 0.5);
			if (!graph->oriented)
				DrawLine((int)node->x, (int)node->y, (int)adjencyList->node->x, (int)adjencyList->node->y, GREEN);
			else
				drawOrientedCurve(node, adjencyList, &middle);

			DrawText(TextFormat("%d", adjencyList->node->weight), (int)middle.x, (int)middle.y, 30, RED);

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
	graphNodes = graph->arcsList;
	while (graphNodes->next != NULL)
	{
		Arc* node = graphNodes->node;

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
			CheckCollisionPointCircle(*mouse, *currentPoint, 30.0f) && !IsKeyDown(KEY_LEFT_SHIFT) ? 50.f : 30.f,
			(moveStartPoint != -1 && movingNode == node) ? RED : BLUE);
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

	EndDrawing();
}

void drawEdgeWeightEditBox(int show, Rectangle* textBox, char* edgeWeight, int letterCount, int framesCounter)
{
	DrawRectangleRec(*textBox, LIGHTGRAY);
	DrawRectangleLines((int)textBox->x, (int)textBox->y, (int)textBox->width, (int)textBox->height, RED);
	DrawText(edgeWeight, (int)textBox->x + letterCount * 5, (int)textBox->y + 8, 40, MAROON);


	if (letterCount < MAX_INPUT_CHARS)
	{
		// Draw blinking underscore char
		if (framesCounter > 50) DrawText("_", (int)textBox->x + 8 + MeasureText(edgeWeight, 40), (int)textBox->y + 12, 40, MAROON);
	}
	else DrawText("Press BACKSPACE to delete chars...", (int)textBox->x, (int)textBox->y - 20, 20, GRAY);
}

void drawOrientedCurve(Arc* node, ListSuccessor* adjencyList, Vector2* middle)
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
	//DrawLine(node->x, node->y, node->x + control1.x, node->y + control1.y, PURPLE);
	//DrawLine(adjencyList->node->x, adjencyList->node->y, 
	//	adjencyList->node->x + control1.x, adjencyList->node->y + control1.y, PURPLE);
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
		RED);
	DrawSplineSegmentBezierCubic(*middle, (Vector2) { middle->x, middle->y },
		(Vector2) {
		adjencyList->node->x + normalNormalized.x, adjencyList->node->y + normalNormalized.y
	},
		(Vector2) {
		adjencyList->node->x, adjencyList->node->y
	},
		2,
		RED);
	Vector2 backVertice = Vector2Subtract(*middle, colinear);

	multiplier = 0.2f;
	normalNormalized.x *= multiplier;
	normalNormalized.y *= multiplier;

	DrawTriangle(*middle,
		Vector2Add(backVertice, normalNormalized),
		Vector2Subtract(backVertice, normalNormalized), GREEN);
}



//Suppression d'un node
//Suppression d'un edge