#include <iostream>
#include "raylib.h"

using namespace std;

int main()
{
    int width{1280};
    int height{720};

    // Initialize the window with specified width, height, and title
    InitWindow(width, height, "Sorin's Window");

    // Circle coordinates and radius
    int circle_x{200};
    int circle_y{200};
    int circle_radius{25};

    // Axe coordinates, length, and movement direction
    int axe_x{400};
    int axe_y{0};
    int axe_length{50};
    int direction{10};

    // Flag to track if the game is over
    bool game_over = false;

    // Set the target frames per second (FPS)
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Begin drawing on the window
        BeginDrawing();

        // Clear the background with a white color
        ClearBackground(WHITE);

        // Game logic begins

        // Check if the game is not over
        if (!game_over)
        {
            // Check collision with the axe
            bool collision_with_axe = (circle_y + circle_radius >= axe_y) &&
                                      (circle_y - circle_radius <= axe_y + axe_length) &&
                                      (circle_x + circle_radius >= axe_x) &&
                                      (circle_x - circle_radius <= axe_x + axe_length);

            // If there is a collision with the axe, set the game_over flag to true
            if (collision_with_axe)
            {
                game_over = true;
            }

            // Draw the circle and rectangle (axe)
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // Move the axe vertically based on the direction
            axe_y += direction;

            // Change the direction if the axe reaches the window boundaries
            if (axe_y > height - axe_length || axe_y < 0)
            {
                direction = -direction;
            }

            // Move the circle based on user input
            if (IsKeyDown(KEY_D) && circle_x < width - circle_radius)
            {
                circle_x += 10;
            }
            if (IsKeyDown(KEY_A) && circle_x > circle_radius)
            {
                circle_x -= 10;
            }
            if (IsKeyDown(KEY_W) && circle_y > circle_radius)
            {
                circle_y -= 10;
            }
            if (IsKeyDown(KEY_S) && circle_y < height - circle_radius)
            {
                circle_y += 10;
            }
        }
        else
        {
            // Game over, display a prompt for replay
            const char *gameOverText = "Game Over!";
            const char *replayText = "Press R to replay";

            // Measure the size of the text for centering it on the screen
            Vector2 gameOverTextSize = MeasureTextEx(GetFontDefault(), gameOverText, 30, 1);
            Vector2 replayTextSize = MeasureTextEx(GetFontDefault(), replayText, 20, 1);

            int gameOverTextX = width / 2 - gameOverTextSize.x / 2;
            int replayTextX = width / 2 - replayTextSize.x / 2;

            // Draw the game over text and replay prompt
            DrawTextEx(GetFontDefault(), gameOverText, {static_cast<float>(gameOverTextX), 200}, 30, 1, RED);
            DrawTextEx(GetFontDefault(), replayText, {static_cast<float>(replayTextX), 250}, 20, 1, BLACK);

            // Check if the R key is pressed to reset the game state and positions
            if (IsKeyPressed(KEY_R))
            {
                game_over = false;
                circle_x = 200;
                circle_y = 200;
                axe_y = 0;
                direction = 10;
            }
        }

        // Game Logic ends;
        // End drawing on the window
        EndDrawing();
    }

    // Close the window and resources
    CloseWindow();
}
