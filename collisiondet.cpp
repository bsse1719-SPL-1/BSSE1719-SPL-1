
#include "raylib.h"
#include <math.h>

int main() {
    InitWindow(800, 450, "Gravitational Attraction");

    Vector2 position = {100, 200};
    Vector2 velocity = {0, 0};
    Vector2 planet2 = {600, 50};
    Vector2 planet = {600, 350};

    float planetMass = 3.0f;
    float gravityStrength = 1000000.0f;
    float planetRadius = 30.0f;
    float planetMass2 = 1.50f;
    float planetRadius2 = 35.0f;

    // ADDED: Moving object's radius and game-over state
    float objectRadius = 10.0f;
    bool gameOver = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Direction from ball to planet
        float dx = planet.x - position.x;
        float dy = planet.y - position.y;
        float dx2 = planet2.x - position.x;
        float dy2 = planet2.y - position.y;

        // Squared distance
        float distanceSquared = dx * dx + dy * dy;
        float distanceSquared2 = dx2 * dx2 + dy2 * dy2;

        // ADDED: Collision detection using the sum of radii
        if (distanceSquared <=
                (planetRadius + objectRadius) *
                (planetRadius + objectRadius) ||
            distanceSquared2 <=
                (planetRadius2 + objectRadius) *
                (planetRadius2 + objectRadius)) {
            gameOver = true;
        }

        // Avoid extreme acceleration inside the planet
        if (!gameOver &&
            distanceSquared > planetRadius * planetRadius &&
            distanceSquared2 > planetRadius2 * planetRadius2) {

            float distance = sqrtf(distanceSquared);
            float distance2 = sqrtf(distanceSquared2);

            // Gravitational acceleration magnitude
            float a1 = gravityStrength * planetMass
                      / distanceSquared;
            float a2 = gravityStrength * planetMass2
                      / distanceSquared2;

            // Convert direction into a unit vector,
            // then multiply by acceleration magnitude
            float ax = (dx / distance) * a1
                     + (dx2 / distance2) * a2;
            float ay = (dy / distance) * a1
                     + (dy2 / distance2) * a2;

            // Update velocity
            velocity.x += ax * dt;
            velocity.y += ay * dt;

            // Update position
            position.x += velocity.x * dt;
            position.y += velocity.y * dt;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircleV(planet, planetRadius, GREEN);
        DrawCircleV(planet2, planetRadius2, BLUE);
        DrawCircleV(position, objectRadius, RED);

        DrawText("Planet1", 565, 400, 20, WHITE);
        DrawText("Planet2", 565, 95, 20, WHITE);
        DrawText("Moving object", 35, 170, 20, WHITE);

        // ADDED: Animated GAME OVER alert
        if (gameOver) {
            float pulse = sinf((float)GetTime() * 5.0f);

            int fontSize = 45 + (int)(8 * (1.0f + pulse));
            Color alertColor = pulse > 0 ? RED : ORANGE;

            const char *message = "GAME OVER";
            int textWidth = MeasureText(message, fontSize);

            DrawRectangle(0, 0, 800, 450,
                          (Color){0, 0, 0, 150});

            DrawText(message,
                     (800 - textWidth) / 2,
                     175,
                     fontSize,
                     alertColor);

            const char *subtitle = "You collided with a planet!";
            int subtitleWidth = MeasureText(subtitle, 20);

            DrawText(subtitle,
                     (800 - subtitleWidth) / 2,
                     245,
                     20,
                     WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
