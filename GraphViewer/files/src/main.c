#include <stdlib.h>
#include <stdio.h>
#include "../include/graph.h"
#include "../include/display.h"

#include "../../../S2/include/dijkstra.h"
#include "../../../S2/include/bellman.h"
#include "../../../S2/include/edgeColoration.h"

#include "../../../S2/textbox.c"
#include "../../../S2/displayLabyrinth1.c"
#include "../../../S2/displayLabyrinth2.c"
#include "../../../S2/graphProject.c"

typedef enum {
    STATE_MENU,
    STATE_LABYRINTH1,
    STATE_LABYRINTH2,
    STATE_GRAPH1,
    STATE_GRAPH2
} GameState;


int main()
{
	InitWindow(670,400,"Projet C");

	Graph* graph1Json = jsonCreateGraphFromFile("C:/Users/guill/CLionProjects/GraphEscapeGame/GraphViewer/resources/graph1.json");
	Graph* graph2Json = jsonCreateGraphFromFile("C:/Users/guill/CLionProjects/GraphEscapeGame/GraphViewer/resources/graph2.json");

	FILE *file1 = fopen("C:/Users/guill/CLionProjects/GraphEscapeGame/S2/ressources/monsterLevel1.txt", "r");
    FILE *file2 = fopen("C:/Users/guill/CLionProjects/GraphEscapeGame/S2/ressources/monsterLevel2.txt", "r");

    Graphe *graph1 = lectureGraphe(file1);
    Graphe *graph2 = lectureGraphe(file2);

    int shortestPath1 = BellmanFord(graph1, 1, 14);
    int shortestPath2 = dijkstra(graph2, 0, 8);
	int longestPath = dijkstraMax(graph2, 0,8);
	int colorationEdge = edgeColoration(graph1,0);
	
    Rectangle level1 = {60,300,100,40};
	Rectangle graphLevel1 = {60,350,100,40};
    Rectangle level2 = {210,300,100,40};
	Rectangle graphLevel2 = {210,350,100,40};
    Rectangle level3 = {360,300,100,40};
	Rectangle graphLevel3 = {360,350,100,40};
    Rectangle level4 = {510,300,100,40};
	Rectangle graphLevel4 = {510,350,100,40};

    GameState currentState = STATE_MENU;

    int stateScore1 = -1;
    int stateScore2 = -1;

    Vector2 mousePosition;

    bool mouseOnText = false;
    int letterCount = 0;
    char name[4] = "\0";
    char name2[4] = "\0";
    int framesCounter = 0;
    Rectangle textBox = {550, 20, 100, 40};

    Image image = LoadImage("C:/Users/guill/CLionProjects/GraphEscapeGame/S2/ressources/lab.png");
    Texture2D texture = LoadTextureFromImage(image);
    texture.height = 400;
    texture.width = 670;       
    UnloadImage(image); 

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 48) && (key <= 57) && (letterCount < 3))
                {
                    name[letterCount] = (char)key;
                    name2[letterCount] = (char)key;
                    name[letterCount+1] = '\0';
                    name2[letterCount+1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();  
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
                name2[letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER)) 
            {
                int temp = TextToInteger(name);
                int temp2 = TextToInteger(name2);
                if (shortestPath1 != temp) stateScore1 = 0;
                else stateScore1 = 1;
                if (shortestPath2 != temp2) stateScore2 = 0;
                else stateScore2 = 1;
            }
        }

        if (currentState == STATE_MENU)
        {
            DrawTexture(texture, 0, 0, WHITE);

            DrawText("WELCOME TO ESCAPE MONSTER", 50, 150, 35, WHITE);
            DrawText("SELECT A LEVEL", 250, 210, 20, WHITE);

            DrawRectangleRec(level1, BLACK);
			DrawRectangleRec(graphLevel1, BLACK);
            DrawRectangleRec(level2, BLACK);
			DrawRectangleRec(graphLevel2, BLACK);
            DrawRectangleRec(level3, BLACK);
			DrawRectangleRec(graphLevel3, BLACK);
            DrawRectangleRec(level4, BLACK);
			DrawRectangleRec(graphLevel4, BLACK);

            DrawText("LEVEL 1", 65, 310, 20, WHITE);
			DrawText("GRAPH 1", 65, 360, 20, WHITE);
            DrawText("LEVEL 2", 215, 310, 20, WHITE);
			DrawText("GRAPH 2", 215, 360, 20, WHITE);
            DrawText("LEVEL 3", 365, 310, 20, WHITE);
			DrawText("GRAPH 3", 365, 360, 20, WHITE);
            DrawText("LEVEL 4", 515, 310, 20, WHITE);
			DrawText("GRAPH 4", 515, 360, 20, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, level1))
                {
                    currentState = STATE_LABYRINTH1;
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, level2))
                {
                    currentState = STATE_LABYRINTH2;
                }
            }

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, graphLevel1))
                {
                    currentState = STATE_GRAPH1;
                }
            }

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, graphLevel2))
                {
                    currentState = STATE_GRAPH2;
                }
            }
        }

        else if (currentState == STATE_LABYRINTH1)
        {
            displayLabyrinth1();
            drawTextBox(mouseOnText, textBox, name, letterCount, framesCounter);

            if (stateScore1 == 0) DrawText("WRONG !", 400,20,30, RED);
            else if (stateScore1 == 1) DrawText("RIGHT !", 400,20,30, GREEN);
        }

        else if (currentState == STATE_LABYRINTH2)
        {
            displayLabyrinth2();
            drawTextBox(mouseOnText, textBox, name, letterCount, framesCounter);
            if (stateScore2 == 2) DrawText("WRONG !", 400,20,30, RED);
            else if (stateScore2 == 3) DrawText("RIGHT !", 400,20,30, GREEN);
        }

		else if (currentState == STATE_GRAPH1) {
			displayGraphWindow(graph1Json);
			DrawRectangle(220,80,250,40, BLUE);
			DrawText(TextFormat("COLORATION : %d", edgeColoration), 240, 90, 25, BLACK); 
		}
		else if (currentState == STATE_GRAPH2) {
			displayGraphWindow(graph2Json);
			DrawRectangle(150,100,200,40, BLUE);
			DrawText(TextFormat("MAX PATH : %d", longestPath), 160, 110, 25, BLACK);
		}
        EndDrawing();
    }
    UnloadTexture(texture);
	CloseWindow();
	
	return 0;
}

