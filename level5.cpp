
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
    float health = 100.0f;
    float maxHealth = 100.0f;

    float fuel = 100.0f;
    float maxFuel = 100.0f;

    float fuelConsumption = 25.0f;
    float fuelRegeneration = 12.0f;

    // Destination
    Vector2 destination = {1300, 400};
    float destinationRadius = 35.0f;

    // Six planets
    const int planetCount = 10;

    Vector2 planets[planetCount] = {
        {100, 230},
        {350, 450},
        {300, 300},
        {400, 590},
        {500, 480},
        {600, 311},
        {700, 400},
        {800, 190},
        {900, 670},
        {1000, 521}
    };

    float planetMasses[planetCount] = {
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,1.0,1.0,1.0
    };

    float planetRadii[planetCount] = {
        20, 20,20,20,20,20,20,20,20,20
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

        bool accelerating = false;

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ||
            IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W) ||
            IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S))
        {
            accelerating = true;
        }

        if (accelerating && fuel > 0.0f)
        {
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
                velocity.x += playerAcceleration * dt;

            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
                velocity.x -= playerAcceleration * dt;

            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
                velocity.y += playerAcceleration * dt;

            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
                velocity.y -= playerAcceleration * dt;

            fuel -= fuelConsumption * dt;

            if (fuel < 0.0f)
                fuel = 0.0f;
        }
        else
        {
            fuel += fuelRegeneration * dt;

            if (fuel > maxFuel)
                fuel = maxFuel;
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
    fuel = 100.0f;

    gameOver = false;
    destinationReached = false;
    outsideMap = false;
}
        //                                                              Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Drawing a simple dotted route from start to destination
        for (int x = (int)start.x;
             x < (int)destination.x; x += 40) {
            DrawCircle(x, (int)start.y, 2, DARKGRAY);
        }




        //                                                      Drawing the starting point
        DrawCircleV(start, 20, DARKGREEN);
        DrawCircleV(start, 12, GREEN);
        DrawText("Start", (int)start.x - 30,
                 (int)start.y + 30, 20, GREEN);






        //                                                        Drawing the destination
       // ******** DRAWING THE WORMHOLE ********

            float time = (float)GetTime();

            // Outer glowing layers
            DrawCircleV(destination, 55, Fade(PURPLE, 0.15f));
            DrawCircleV(destination, 45, Fade(SKYBLUE, 0.2f));

            // Dark center of the wormhole
            DrawCircleV(destination, 32, BLACK);

            // Rotating wormhole rings
            DrawRing(
                destination,
                30, 36,
                time * 80,
                time * 80 + 240,
                64,
                Fade(SKYBLUE, 0.9f)
            );

            DrawRing(
                destination,
                37, 42,
                -time * 100,
                -time * 100 + 220,
                64,
                Fade(PURPLE, 0.9f)
            );

            DrawRing(
                destination,
                44, 48,
                time * 120,
                time * 120 + 180,
                64,
                Fade(VIOLET, 0.8f)
            );

            // Glowing outer boundary
            DrawCircleLines(
                (int)destination.x,
                (int)destination.y,
                55,
                Fade(SKYBLUE, 0.7f)
            );

            // Small rotating particles
            for (int i = 0; i < 8; i++)
            {
                float angle = time * 2.0f + i * (PI / 4);

                float x = destination.x + cosf(angle) * 52;
                float y = destination.y + sinf(angle) * 52;

                DrawCircle(
                    (int)x,
                    (int)y,
                    3,
                    SKYBLUE
                );
            }

            // Portal label
            DrawText(
                "WORMHOLE",
                (int)destination.x - 55,
                (int)destination.y + 68,
                20,
                SKYBLUE
            );


        //                                                   Drawing all planets and their labels
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






            //                                 Small highlight to give the planets some depth
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

        // ******Health bar*******
        DrawText("HULL INTEGRITY", 20, 600, 18, WHITE);

        DrawRectangle(20, 625, 200, 18, DARKGRAY);

        float healthWidth = 200.0f * (health / maxHealth);

        Color healthColor = GREEN;

        if (health < 60.0f)
            healthColor = ORANGE;

        if (health < 30.0f)
            healthColor = RED;

        DrawRectangle(20, 625, (int)healthWidth, 18, healthColor);


        //                         ******Fuel bar*******
        DrawText("THRUSTER FUEL", 20, 660, 18, WHITE);

        DrawRectangle(20, 685, 200, 18, DARKGRAY);

        float fuelWidth = 200.0f * (fuel / maxFuel);

        Color fuelColor = GOLD;

        if (fuel < 30.0f)
            fuelColor = RED;

        DrawRectangle(20, 685, (int)fuelWidth, 18, fuelColor);

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


            // Restart prompt


            float restartPulse = sinf((float)GetTime() * 3.0f);
            Color restartColor = restartPulse > 0 ? GOLD : WHITE;

            const char *restartMessage = "PRESS R TO RESTART";
            int restartWidth = MeasureText(restartMessage, 22);

            DrawRectangle(
                (screenWidth - restartWidth) / 2 - 20,
                screenHeight / 2 + 75,
                restartWidth + 40,
                42,
                (Color){30, 30, 30, 200}
            );

            DrawText(
                restartMessage,
                (screenWidth - restartWidth) / 2,
                screenHeight / 2 + 85,
                22,
                restartColor
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


            // Restart prompt


            float restartPulse = sinf((float)GetTime() * 3.0f);
            Color restartColor = restartPulse > 0 ? GOLD : WHITE;

            const char *restartMessage = "PRESS R TO RESTART";
            int restartWidth = MeasureText(restartMessage, 22);

            DrawRectangle(
                (screenWidth - restartWidth) / 2 - 20,
                screenHeight / 2 + 45,
                restartWidth + 40,
                42,
                (Color){30, 30, 30, 200}
            );

            DrawText(
                restartMessage,
                (screenWidth - restartWidth) / 2,
                screenHeight / 2 + 55,
                22,
                restartColor
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


            // Restart prompt



            float restartPulse = sinf((float)GetTime() * 3.0f);
            Color restartColor = restartPulse > 0 ? GOLD : WHITE;

            const char *restartMessage = "PRESS R TO RESTART";
            int restartWidth = MeasureText(restartMessage, 22);

            DrawRectangle(
                (screenWidth - restartWidth) / 2 - 20,
                screenHeight / 2 + 75,
                restartWidth + 40,
                42,
                (Color){30, 30, 30, 200}
            );

            DrawText(
                restartMessage,
                (screenWidth - restartWidth) / 2,
                screenHeight / 2 + 85,
                22,
                restartColor
            );

        }


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
