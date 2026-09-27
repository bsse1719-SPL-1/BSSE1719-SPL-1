#include "raylib.h"

int main() {
    InitWindow(800, 450, "Space Game");
    double x=0;
    double y = 225;
    float time;
    double t=0;
    double v=0;
    double a=20;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);
        
        DrawCircle(x, y, 20, RED);
        time = GetFrameTime(); 
        v = v + a*time;
        t += time;
        x = x + v*time;
        if(x >= 800){
            v = -v;
        }
        
        
        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}

