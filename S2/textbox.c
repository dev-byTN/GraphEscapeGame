#include "raylib.h"
#include <stdio.h>

int drawTextBox(bool mouseOnText, Rectangle textBox, char name[], int letterCount, int framesCounter)
{

    DrawRectangleRec(textBox, WHITE);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

    if (mouseOnText)
    {
        if (letterCount < 3)
        {
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
    }

    return 0;
}


int createTextBox(bool mouseOnText, Rectangle textBox, char name[], int letterCount, int framesCounter)
{
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
                    name[letterCount+1] = '\0'; 
                    letterCount++;
                }

                key = GetCharPressed();  
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }

            
        }
}
