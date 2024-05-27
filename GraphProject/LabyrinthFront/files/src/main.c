#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/graph.h"
#include "../include/display.h"

#include "../../../LabyrinthBackEnd/src/dijkstra.c"
#include "../../../LabyrinthBackEnd/src/bellman.c"
#include "../../../LabyrinthBackEnd/src/edgecoloration.c"
#include "../../../LabyrinthBackEnd/src/textbox.c"
#include "../../../LabyrinthBackEnd/src/displayLabyrinth1.c"
#include "../../../LabyrinthBackEnd/src/displayLabyrinth2.c"
#include "../../../LabyrinthBackEnd/src/graphProject.c"

typedef enum {
    STATE_MENU,
    STATE_LABYRINTH1,
    STATE_LABYRINTH2,
    STATE_GRAPH1,
    STATE_GRAPH2,
    NONE
} GameState;


int main() {
    InitWindow(670, 400, "Projet C");

    Graph *graph1Json = jsonCreateGraphFromFile(
            "../../resources/graph1.json");
    Graph *graph2Json = jsonCreateGraphFromFile(
            "../../resources/graph2.json");

    FILE *file1 = fopen("../../../LabyrinthBackEnd/ressources/monsterLevel1.txt", "r");
    FILE *file2 = fopen("../../../LabyrinthBackEnd/ressources/monsterLevel2.txt", "r");

    Graphe *graph1 = lectureGraphe(file1);
    Graphe *graph2 = lectureGraphe(file2);

    Rectangle level1 = {60, 300, 100, 40};
    Rectangle graphLevel1 = {60, 350, 100, 40};
    Rectangle level2 = {210, 300, 100, 40};
    Rectangle graphLevel2 = {210, 350, 100, 40};
    Rectangle level3 = {360, 300, 100, 40};
    Rectangle graphLevel3 = {360, 350, 100, 40};
    Rectangle level4 = {510, 300, 100, 40};
    Rectangle graphLevel4 = {510, 350, 100, 40};
    Rectangle textBox = {550, 20, 100, 40};
    Rectangle textBoxColoration = {220, 80, 250, 40};
    Rectangle textBoxLongestPath = {150, 100, 200, 40};

    GameState currentState = STATE_MENU;

    Vector2 mousePosition;

    int shortestPath1 = BellmanFord(graph1, 1, 14);
    int shortestPath2 = dijkstra(graph2, 0, 8 - 1);
    int longestPath = dijkstraMax(graph2, 0, 8 - 1);
    int colorationEdge = edgeColoration(graph1, 0);

    int stateScore1 = -1;
    int stateScore2 = -1;
    int stateScore1bis = -1;
    int stateScore2bis = -1;

    int letterCount1 = 0;
    int letterCount2 = 0;
    int letterCount1bis = 0;
    int letterCount2bis = 0;

    int framesCounter = 0;

    bool mouseOnText = false;
    bool mouseOnText2 = false;
    bool mouseOnText3 = false;

    char name[4] = "\0";
    char name2[4] = "\0";
    char name1bis[4] = "\0";
    char name2bis[4] = "\0";

    Image image = LoadImage("../../../LabyrinthBackEnd/ressources/lab.png");
    Texture2D texture = LoadTextureFromImage(image);
    texture.height = 400;
    texture.width = 670;
    UnloadImage(image);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (CheckCollisionPointRec(GetMousePosition(), textBoxColoration)) mouseOnText2 = true;
        else mouseOnText2 = false;

        if (CheckCollisionPointRec(GetMousePosition(), textBoxLongestPath)) mouseOnText3 = true;
        else mouseOnText3 = false;

        GameState nextState = NONE;

        if (mouseOnText) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            if ((key >= 48) && (key <= 57)) {
                if (currentState == STATE_LABYRINTH1 && letterCount1 < 3) {
                    name[letterCount1] = (char) key;
                    name[letterCount1 + 1] = '\0';
                    letterCount1++;
                }
                if (currentState == STATE_LABYRINTH2 && letterCount2 < 3) {
                    name2[letterCount2] = (char) key;
                    name2[letterCount2 + 1] = '\0';
                    letterCount2++;
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {

                if (currentState == STATE_LABYRINTH1) {
                    --letterCount1;
                    if (letterCount1 < 0) {
                        letterCount1 = 0;
                    }
                    name[letterCount1] = '\0';
                } 
                else if (currentState == STATE_LABYRINTH2) {
                    --letterCount2;
                    if (letterCount2 < 0) {
                        letterCount2 = 0;
                    }
                    name2[letterCount2] = '\0';
                }

            }

            if (IsKeyPressed(KEY_ENTER)) 
            {
                if (currentState == STATE_LABYRINTH1) 
                {
                    int temp = TextToInteger(name);
                    if (shortestPath1 != temp) {
                        stateScore1 = 0;
                    } else {
                        stateScore1 = 1;
                        nextState = STATE_GRAPH1;
                    }
                } 
                
                else if (currentState == STATE_LABYRINTH2) 
                {
                    int temp2 = TextToInteger(name2);
                    if (shortestPath2 != temp2) {
                        stateScore2 = 2;
                    } else {
                        stateScore2 = 3;
                        nextState = STATE_GRAPH2;
                    }
                }
            }
        }

        if (mouseOnText2) 
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            if ((key >= 48) && (key <= 57))
            {
                if (currentState == STATE_GRAPH1 && letterCount1bis < 3) {
                    name1bis[letterCount1bis] = (char) key;
                    name1bis[letterCount1bis + 1] = '\0';
                    letterCount1bis++;
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (currentState == STATE_GRAPH1) {
                    --letterCount1bis;
                    if (letterCount1bis < 0) {
                        letterCount1bis = 0;
                    }
                    name1bis[letterCount1bis] = '\0';
                }
            }

            if(IsKeyPressed(KEY_ENTER))
            {
                if (currentState == STATE_GRAPH1) 
                {
                    int temp3 = TextToInteger(name1bis);
                    if (colorationEdge != temp3) {
                        stateScore1bis = 4;
                    } else {
                        stateScore1bis = 5;
                        nextState = STATE_LABYRINTH2;
                    }
                }
            }
            
        }

        if (mouseOnText3) 
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            if ((key >= 48) && (key <= 57))
            {
                if (currentState == STATE_GRAPH2 && letterCount2bis < 3) {
                    name2bis[letterCount2bis] = (char) key;
                    name2bis[letterCount2bis + 1] = '\0';
                    letterCount2bis++;
                }
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (currentState == STATE_GRAPH2) {
                    --letterCount2bis;
                    if (letterCount2bis < 0) {
                        letterCount2bis = 0;
                    }
                    name2bis[letterCount2bis] = '\0';
                }
            }

            if(IsKeyPressed(KEY_ENTER))
            {
                if (currentState == STATE_GRAPH2) 
                {
                    int temp4 = TextToInteger(name2bis);
                    if (longestPath != temp4) {
                        stateScore2bis = 6;
                    } else {
                        stateScore2bis = 7;
                        nextState = STATE_MENU;
                    }
                }
            }
        }

        if (currentState == STATE_MENU) {
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

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, level1)) {
                    currentState = STATE_LABYRINTH1;
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, level2)) {
                    currentState = STATE_LABYRINTH2;
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, graphLevel1)) {
                    currentState = STATE_GRAPH1;
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, graphLevel2)) {
                    currentState = STATE_GRAPH2;
                }
            }
        } 
        
        else if (currentState == STATE_LABYRINTH1) 
        {
            displayLabyrinth1();
            drawTextBox(mouseOnText, textBox, name, letterCount1, framesCounter);

            if (stateScore1 == 0) DrawText("WRONG !", 400, 20, 30, RED);
            else if (stateScore1 == 1) DrawText("RIGHT !", 400, 20, 30, GREEN);
        } 

        else if (currentState == STATE_LABYRINTH2) 
        {
            displayLabyrinth2();
            drawTextBox(mouseOnText, textBox, name2, letterCount2, framesCounter);
            if (stateScore2 == 2) DrawText("WRONG !", 400, 20, 30, RED);
            else if (stateScore2 == 3) DrawText("RIGHT !", 400, 20, 30, GREEN);
        } 

        else if (currentState == STATE_GRAPH1) 
        {
            displayGraphWindow(graph1Json);
            drawTextBoxColoration(mouseOnText2, textBoxColoration, name1bis, letterCount1bis, framesCounter);
            DrawText(TextFormat("COLORATION : "), 240, 90, 25, BLACK);
            if (stateScore1bis == 4) DrawText("WRONG !", 400, 20, 30, RED);
            else if (stateScore1bis == 5) DrawText("RIGHT !", 400, 20, 30, GREEN); 
        } 

        else if (currentState == STATE_GRAPH2) 
        {
            displayGraphWindow(graph2Json);
            drawTextBoxMaxPath(mouseOnText3, textBoxLongestPath, name2bis,letterCount2bis, framesCounter);
            DrawText(TextFormat("MAX PATH : "), 160, 110, 25, BLACK);
            if (stateScore2bis == 6) DrawText("WRONG !", 180, 150, 30, RED);
            else if (stateScore2bis == 7) DrawText("RIGHT !", 180, 150, 30, GREEN);
        }

        if (nextState != NONE) {
            currentState = nextState;
        }

        EndDrawing();
    }
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}

