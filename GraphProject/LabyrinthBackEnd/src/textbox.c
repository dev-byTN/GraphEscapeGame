#include "raylib.h"
#include <stdio.h>

int drawTextBox(bool mouseOnText, Rectangle textBox, char name[], int letterCount, int framesCounter)
{

    DrawRectangleRec(textBox, BLUE);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, WHITE);

    if (mouseOnText)
    {
        if (letterCount < 3)
        {
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, WHITE);
        }
    }

    return 0;
}

int drawTextBoxColoration(bool mouseOnText, Rectangle textBox, char name[], int letterCount, int framesCounter)
{

    DrawRectangleRec(textBox, BLUE);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);

    DrawText(name, (int)textBox.x + 200, (int)textBox.y + 10, 25, BLACK);

    if (mouseOnText)
    {
        if (letterCount < 3)
        {
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 200 + MeasureText(name, 40), (int)textBox.y + 12, 40, WHITE);
        }
    }

    return 0;
}


int drawTextBoxMaxPath(bool mouseOnText, Rectangle textBox, char name[], int letterCount, int framesCounter)
{

    DrawRectangleRec(textBox, BLUE);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);

    DrawText(name, (int)textBox.x + 165, (int)textBox.y + 10, 25, BLACK);

    if (mouseOnText)
    {
        if (letterCount < 3)
        {
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 165 + MeasureText(name, 40), (int)textBox.y + 12, 40, WHITE);
        }
    }

    return 0;
}
