#include "raylib.h"

int displayLabyrinth2()
{
    DrawRectangle(200, 0, 20, 120,BLUE);
    DrawRectangle(60, 120, 20, 140,BLUE);
    DrawRectangle(350, 80, 180, 20,BLUE);
    DrawRectangle(0, 320, 220, 20,BLUE);
    DrawRectangle(350, 300, 100, 20,BLUE);
    DrawRectangle(350, 250, 100, 20,BLUE);
    DrawRectangle(200, 250, 20, 80,BLUE);
    DrawRectangle(80, 170, 260, 20,BLUE);
    DrawRectangle(430, 170, 20, 80,BLUE);
    DrawRectangle(430, 150, 100, 20,BLUE);
    DrawRectangle(510, 250, 20, 200,BLUE);

    DrawText("IN", 25, 25, 20, BLUE);
    DrawText("7", 480, 25, 20, WHITE);
    DrawText("23", 60, 380, 20, WHITE);
    DrawText("1", 400, 380, 20, WHITE);
    DrawText("10", 260, 240, 20, WHITE);
    DrawText("9", 25, 200, 20, WHITE);
    DrawText("13", 575, 150, 20, WHITE);
    DrawText("10", 380, 130, 20, WHITE);
    DrawText("OUT", 550, 330, 20, BLUE);
    DrawText("20", 380, 210, 20, WHITE);
    DrawText("3", 260, 310, 20, WHITE);
    DrawText("8", 430, 280, 20, WHITE);
    DrawText("6", 575, 260, 20, WHITE);
    DrawText("14", 150, 130, 20, WHITE);
    DrawText("3", 480, 130, 20, WHITE);

    return 0;
}
