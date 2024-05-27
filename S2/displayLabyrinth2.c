#include "raylib.h"

int displayLabyrinth2()
{
    DrawRectangle(200, 0, 20, 120,BLACK);
    DrawRectangle(60, 120, 20, 140,BLACK);
    DrawRectangle(350, 80, 180, 20,BLACK);
    DrawRectangle(0, 320, 220, 20,BLACK);
    DrawRectangle(350, 300, 100, 20,BLACK);
    DrawRectangle(350, 250, 100, 20,BLACK);
    DrawRectangle(200, 250, 20, 80,BLACK);
    DrawRectangle(80, 170, 260, 20,BLACK);
    DrawRectangle(430, 170, 20, 80,BLACK);
    DrawRectangle(430, 150, 100, 20,BLACK);
    DrawRectangle(510, 250, 20, 200,BLACK);

    DrawText("IN", 25, 25, 20, RED);
    DrawText("7", 480, 25, 20, BLACK);
    DrawText("23", 60, 380, 20, BLACK);
    DrawText("1", 400, 380, 20, BLACK);
    DrawText("10", 260, 240, 20, BLACK);
    DrawText("9", 25, 200, 20, BLACK);
    DrawText("13", 575, 150, 20, BLACK);
    DrawText("10", 380, 130, 20, BLACK);
    DrawText("OUT", 550, 330, 20, RED);
    DrawText("20", 380, 210, 20, BLACK);
    DrawText("3", 260, 310, 20, BLACK);
    DrawText("8", 430, 280, 20, BLACK);
    DrawText("6", 575, 260, 20, BLACK);
    DrawText("14", 150, 130, 20, BLACK);
    DrawText("3", 480, 130, 20, BLACK);

    return 0;
}
