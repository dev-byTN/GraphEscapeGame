#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    InitWindow(600, 400, "GraphProject");

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(0, 75, 190, 40,BLACK);
            DrawRectangle(60, 100, 40, 180,BLACK);
            DrawRectangle(250, 75, 210, 40,BLACK);
            DrawRectangle(530, 75, 40, 210,BLACK);
            DrawRectangle(0, 330, 100, 40,BLACK);
            DrawRectangle(150, 330, 310, 40,BLACK);
            DrawRectangle(530, 330, 40, 40,BLACK);
            DrawRectangle(420, 240, 40, 40,BLACK);
            DrawRectangle(340, 240, 40, 40,BLACK);
            DrawRectangle(250, 170, 40, 110,BLACK);
            DrawRectangle(150, 170, 40, 110,BLACK);
            DrawRectangle(250, 170, 210, 40,BLACK);


            DrawText("IN", 25, 25, 20, RED);
            DrawText("10", 330, 25, 20, BLACK);
            DrawText("5", 210, 90, 20, BLACK);
            DrawText("5", 500, 90, 20, BLACK);
            DrawText("2", 500, 170, 20, BLACK);
            DrawText("15", 500, 250, 20, BLACK);
            DrawText("5", 500, 350, 20, BLACK);
            DrawText("2", 120, 350, 20, BLACK);
            DrawText("5", 60, 380, 20, BLACK);
            DrawText("15", 260, 380, 20, BLACK);
            DrawText("15", 25, 230, 20, BLACK);
            DrawText("7", 585, 350, 20, BLACK);
            DrawText("20", 575, 130, 20, BLACK);
            DrawText("20", 330, 130, 20, BLACK);
            DrawText("15", 120, 250, 20, BLACK);
            DrawText("10", 160, 300, 20, BLACK);
            DrawText("10", 260, 300, 20, BLACK);
            DrawText("10", 345, 300, 20, BLACK);
            DrawText("14", 430, 300, 20, BLACK);
            DrawText("OUT", 480, 300, 20, RED);
            DrawText("2", 550, 300, 20, BLACK);
            DrawText("30", 210, 220, 20, BLACK);
            DrawText("5", 345, 220, 20, BLACK);
            DrawText("10", 430, 220, 20, BLACK);
            DrawText("12", 390, 250, 20, BLACK);

            //DrawCircle()
        EndDrawing();
    }

    CloseWindow();

    return 0;
}