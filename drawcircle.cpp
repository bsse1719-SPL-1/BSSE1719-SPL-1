#include "raylib.h"

int main() {
    InitWindow(800, 450, "Space Game");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawCircle(200, 200, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

