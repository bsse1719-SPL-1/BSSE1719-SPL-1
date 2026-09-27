#include "raylib.h"

int main() {
    InitWindow(800, 450, "Space Game");
    double x=0;
    int y = 225;
    double time = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);
        
        DrawCircle(x, y, 20, RED);
        time+=0.001;
        x = x + 0.05*time;

        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}

