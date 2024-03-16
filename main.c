#include "include/raylib.h"

int main(void)
{
    InitWindow(800, 450, "Example");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawText("Template", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
