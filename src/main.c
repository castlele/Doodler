#include <raylib.h>

int main()
{
    InitWindow(800, 600, "Doodler");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);

            DrawRectangle(800/2 - 25, 600/2 - 25, 50, 50, RED);
        EndDrawing();
    }

    return 0;
}
