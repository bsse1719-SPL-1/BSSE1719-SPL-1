
#include "raylib.h"
#include <math.h>



void DrawSpaceship(Vector2 position, float size)
{
    // Main body: points to the right
    DrawTriangle(
        {position.x + size, position.y},
        {position.x - size * 0.7f, position.y - size * 0.5f},
        {position.x - size * 0.7f, position.y + size * 0.5f},
        LIGHTGRAY
    );

    // Upper wing
    DrawTriangle(
        {position.x - size * 0.2f, position.y - size * 0.3f},
        {position.x - size * 0.8f, position.y - size},
        {position.x - size * 0.6f, position.y},
        BLUE
    );

    // Lower wing
    DrawTriangle(
        {position.x - size * 0.2f, position.y + size * 0.3f},
        {position.x - size * 0.8f, position.y + size},
        {position.x - size * 0.6f, position.y},
        BLUE
    );
}







int main() {
    const int screenWidth = 1400;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Space Gravity Game");  // Init Window creates the actual window with a title
    SetTargetFPS(60);  

    // Starting point and moving object
    Vector2 start = {100, 400};
    Vector2 position = start;
    Vector2 velocity = {0, 0};
    Vector2 size = {20.0f, 15.0f};
    float objectRadius = 10.0f;

    // Destination
    Vector2 destination = {1300, 400};
    float destinationRadius = 35.0f;

    // Six planets
    const int planetCount = 6;

    Vector2 planets[planetCount] = {
        {350, 230},
        {500, 570},
        {650, 350},
        {830, 630},
        {1010, 210},
        {1150, 500}
    };

    float planetMasses[planetCount] = {
        2.5f, 3.0f, 2.0f, 2.5f, 3.5f, 2.0f
    };

    float planetRadii[planetCount] = {
        40, 55, 45, 50, 60, 40
    };

    float gravityStrength = 1800000.0f;           //G

    bool gameOver = false;
    bool destinationReached = false;
    bool outsideMap = false;
    float playerAcceleration = 250.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Physics runs only while the game is active
        if (!gameOver && !destinationReached && !outsideMap) {
            // Player controls
if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
    velocity.y -= playerAcceleration * dt;
}

if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
    velocity.y += playerAcceleration * dt;
}

if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    velocity.x -= playerAcceleration * dt;
}

if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    velocity.x += playerAcceleration * dt;
}
            float ax = 0;
            float ay = 0;

            // Calculating gravitational attraction from every planet
            for (int i = 0; i < planetCount; i++) {

                float dx = planets[i].x - position.x;
                float dy = planets[i].y - position.y;

                float distanceSquared = dx * dx + dy * dy;
                float collisionDistance =
                    planetRadii[i] + objectRadius;

                // Check collision with this planet
                if (distanceSquared <=
                    collisionDistance * collisionDistance) {
                    gameOver = true;
                }

                // Add this planet's gravitational acceleration
                if (distanceSquared >
                    collisionDistance * collisionDistance) {

                    float distance = sqrtf(distanceSquared);

                    float acceleration =
                        gravityStrength * planetMasses[i]
                        / distanceSquared;

                    ax += (dx / distance) * acceleration;
                    ay += (dy / distance) * acceleration;
                }
            }
            if(position.x<0 || position.x>1400 || position.y<0 || position.y>800){
                 outsideMap = true;
            }
            // Move only if no collision has occurred
            if (!gameOver) {
                
                velocity.x += ax * dt;
                velocity.y += ay * dt;

                position.x += velocity.x * dt;
                position.y += velocity.y * dt;

                // Check collisions again after movement
                for (int i = 0; i < planetCount; i++) {
                    float dx = planets[i].x - position.x;
                    float dy = planets[i].y - position.y;

                    float distanceSquared =
                        dx * dx + dy * dy;

                    float collisionDistance =
                        planetRadii[i] + objectRadius;

                    if (distanceSquared <=
                        collisionDistance * collisionDistance) {
                        gameOver = true;
                    }
                }

                // Check whether the destination has been reached
                float destX = destination.x - position.x;
                float destY = destination.y - position.y;

                float destDistanceSquared =
                    destX * destX + destY * destY;

                float arrivalDistance =
                    destinationRadius + objectRadius;

                if (!gameOver &&
                    destDistanceSquared <=
                    arrivalDistance * arrivalDistance) {
                    destinationReached = true;
                }
            }
        }
        // Restarting after winning or losing
if ((gameOver || destinationReached || outsideMap) && IsKeyPressed(KEY_R)) {
    position = start;
    velocity = {60, 0};

    gameOver = false;
    destinationReached = false;
    outsideMap = false;
}
        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Drawing a simple dotted route from start to destination
        for (int x = (int)start.x;
             x < (int)destination.x; x += 40) {
            DrawCircle(x, (int)start.y, 2, DARKGRAY);
        }

        // Drawing the starting point
        DrawCircleV(start, 20, DARKGREEN);
        DrawCircleV(start, 12, GREEN);
        DrawText("START", (int)start.x - 30,
                 (int)start.y + 30, 20, GREEN);

        // Drawing the destination
        DrawCircleLines((int)destination.x,
                        (int)destination.y,
                        destinationRadius + 12, GOLD);
        DrawCircleV(destination, destinationRadius, DARKBLUE);
        DrawCircleLines((int)destination.x,
                        (int)destination.y,
                        destinationRadius, SKYBLUE);
        DrawText("DESTINATION",
                 (int)destination.x - 65,
                 (int)destination.y + 50, 20, GOLD);

        // Drawing all planets and their labels
        for (int i = 0; i < planetCount; i++) {
            Color planetColor;

            if (i == 0) {
                planetColor = GREEN;
            } else if (i == 1) {
                planetColor = BLUE;
            } else if (i == 2) {
                planetColor = PURPLE;
            } else if (i == 3) {
                planetColor = DARKBLUE;
            } else if (i == 4) {
                planetColor = RED;
            } else {
                planetColor = SKYBLUE;
            }

            DrawCircleV(planets[i], planetRadii[i], planetColor);

            // Small highlight to give the planets some depth
            DrawCircle(
                (int)(planets[i].x - planetRadii[i] * 0.25f),
                (int)(planets[i].y - planetRadii[i] * 0.25f),
                planetRadii[i] * 0.2f,
                Fade(WHITE, 0.35f)
            );

            DrawText(
                TextFormat("Planet %d", i + 1),
                (int)planets[i].x - 40,
                (int)(planets[i].y + planetRadii[i] + 8),
                18,
                WHITE
            );
        }

        // Drawing the moving object
        DrawSpaceship(position, objectRadius * 2);

        // Display current speed
        float speed = sqrtf(
            velocity.x * velocity.x +
            velocity.y * velocity.y
        );

        DrawText(
            TextFormat("Speed: %.1f MPH", speed),
            20, 20, 22, WHITE
        );

        DrawText(
            "Reach the destination without hitting a planet!",
            20, 55, 22, LIGHTGRAY
        );

        // Animated GAME OVER alert
        if (gameOver) {
            float pulse = sinf((float)GetTime() * 5.0f);

            int fontSize = 45 + (int)(8 * (1.0f + pulse));
            Color alertColor = pulse > 0 ? RED : ORANGE;

            DrawRectangle(
                0, 0, screenWidth, screenHeight,
                (Color){0, 0, 0, 180}
            );

            const char *message = "GAME OVER";
            int textWidth = MeasureText(message, fontSize);

            DrawText(
                message,
                (screenWidth - textWidth) / 2,
                screenHeight / 2 - 50,
                fontSize,
                alertColor
            );

            const char *subtitle = "You collided with a planet!";
            int subtitleWidth = MeasureText(subtitle, 24);

            DrawText(
                subtitle,
                (screenWidth - subtitleWidth) / 2,
                screenHeight / 2 + 25,
                24,
                WHITE
            );
        }

        // Destination reached message
        if (destinationReached) {
            const char *message = "DESTINATION REACHED!";
            int textWidth = MeasureText(message, 45);

            DrawRectangle(
                0, 0, screenWidth, screenHeight,
                (Color){0, 0, 0, 150}
            );

            DrawText(
                message,
                (screenWidth - textWidth) / 2,
                screenHeight / 2 - 20,
                45,
                GREEN
            );
        }

        //Spaceship going outside the map message
        if(outsideMap){
            float pulse = sinf((float)GetTime() * 5.0f);

            int fontSize = 45 + (int)(8 * (1.0f + pulse));
            Color alertColor = pulse > 0 ? RED : ORANGE;

            DrawRectangle(
                0, 0, screenWidth, screenHeight,
                (Color){0, 0, 0, 180}
            );

            const char *message = "GAME OVER";
            int textWidth = MeasureText(message, fontSize);

            DrawText(
                message,
                (screenWidth - textWidth) / 2,
                screenHeight / 2 - 50,
                fontSize,
                alertColor
            );

            const char *subtitle = "You went outside the map!";
            int subtitleWidth = MeasureText(subtitle, 24);

            DrawText(
                subtitle,
                (screenWidth - subtitleWidth) / 2,
                screenHeight / 2 + 25,
                24,
                LIME
            );

        }


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
