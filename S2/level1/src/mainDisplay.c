#include "display.c"

int main()
{
    InitWindow(600, 400, "GraphProject");

    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        //displayLabyrinth();
        displayCircle();
        displaySommets()
        EndDrawing();
    }

    CloseWindow();

    return 0;
}