#include "graph.h"


int displayLabyrinth()
{
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
    

    return 0;
}


/*int displayCircle()
{
    int test = 0;
    //DrawCircleV(200, 200,, BLUE);
    DrawCircle(200,200,150,BLUE);
    DrawText(TextFormat("%s", test), 195, 175, 30, WHITE);
    return 0;
}


int displaySommets(int order, ListSuccessor **successors) {
    for (int i = 0; i < order; i++) {
        Successor *successor = successors[i]->firstSuccessor;
        while (successor != NULL) {
            DrawCircle(10*i, 10*i, 20, BLUE);
            DrawText(TextFormat("%s", successor->sommet), 9*i, 5*i, 30, WHITE);
            successor = successor->nextSuccessor;
        }
    }
    return 0;
}*/