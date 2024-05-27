#include "raylib.h"
#include "level1/src/displayLabyrinth1.c"
#include "level2/displayLabyrinth2.c"
#include <stdio.h>


typedef enum {
    STATE_MENU,
    STATE_LABYRINTH1,
    STATE_LABYRINTH2,
    STATE_LABYRINTH3,
    STATE_LABYRINTH4
} GameState;


int main()
{
    InitWindow(670,400,"Projet C");

    Rectangle level1 = {60,300,100,40};
    Rectangle level2 = {210,300,100,40};
    Rectangle level3 = {360,300,100,40};
    Rectangle level4 = {510,300,100,40};

    GameState currentState = STATE_MENU;

    Vector2 mousePosition;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (currentState == STATE_MENU)
        {
            DrawRectangleRec(level1, BLACK);
            DrawRectangleRec(level2, BLACK);
            DrawRectangleRec(level3, BLACK);
            DrawRectangleRec(level4, BLACK);

            DrawText("LEVEL 1", 65, 310, 20, WHITE);
            DrawText("LEVEL 2", 215, 310, 20, WHITE);
            DrawText("LEVEL 3", 365, 310, 20, WHITE);
            DrawText("LEVEL 4", 515, 310, 20, WHITE);

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
        }

        else if (currentState == STATE_LABYRINTH1)
        {
            displayLabyrinth1();
        }

        else if (currentState == STATE_LABYRINTH2)
        {
            displayLabyrinth2();
        }

        EndDrawing();
    }

    CloseWindow();
}