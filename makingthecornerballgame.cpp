#include "raylib.h"



int main() {
    InitWindow(800, 450, "Space Game");
    double x=0;
    double y = 0;
    float time;
    double t=0;
    double v1=190;
    double v2=190;
    double a=20;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);
        
        DrawCircle(x, y, 20, RED);
        time = GetFrameTime(); 
       

        t += time;
        x = x + v1*time;
        y = y + v2*time;
        if(x >= 800 || x<0){
            v1 = -v1;
        }
         if(y >= 450 || y<0){
            v2 = -v2;
        }
        
        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}

