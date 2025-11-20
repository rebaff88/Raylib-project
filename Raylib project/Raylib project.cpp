#include "raylib.h"

#define MAX_BULLETS 50
#define MAX_ENEMIES 3

struct Bullet

{
    float x, y;
    bool active;
};

struct Enemy {
    float x, y;
    bool active;
};

// Deterministic pseudo-random generator using static counter
int SimpleRand(int min, int max) {
    static int seed = 1;
    seed = (seed * 37 + 13) % 1000;
    return min + seed % (max - min + 1);
}

// Draw player ship using rectangles and circles
void DrawPlayerShip(float x, float y) {
    // Main body
    DrawRectangle(x - 15, y - 10, 30, 20, BLUE);

    // Cockpit
    DrawCircle((int)x, (int)(y - 5), 7, BLUE);

    // Wings
    DrawCircle((int)(x - 18), (int)(y + 5), 6, DARKBLUE);
    DrawCircle((int)(x + 18), (int)(y + 5), 6, DARKBLUE);

    // Exhaust/fire
        DrawCircle((int)(x - 7), (int)(y + 12), 5, ORANGE);
    DrawCircle((int)(x + 7), (int)(y + 12), 5, ORANGE);
}

// Draw enemy ship using circles and rectangles
/*void DrawEnemyShip(float x, float y) {
    DrawRectangle(x - 15, y - 10, 30, 20, RED);
    DrawCircle((int)x, (int)y, 5, ORANGE); // cockpit
}*/

void DrawEnemyShip(float x, float y)
{
    // Main body
    DrawRectangle(x - 15, y - 10, 30, 20, GREEN);

    // Cockpit
    DrawCircle((int)x, (int)(y - 5), 7, RED);

    // Wings
    DrawCircle((int)(x - 18), (int)(y + 5), 6, YELLOW);
    DrawCircle((int)(x + 18), (int)(y + 5), 6, YELLOW);

    // Exhaust/fire
   // DrawCircle((int)(x - 7), (int)(y + 12), 5, ORANGE);
   // DrawCircle((int)(x + 7), (int)(y + 12), 5, ORANGE);
}







int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Space Shooter - Full Version");
    SetTargetFPS(60);

    // Player variables
    float playerX = screenWidth / 2.0f;
    float playerY = screenHeight - 50;
    float playerSpeed = 5.0f;
    int lives = 3;
    int score = 0;

    // Bullets
    Bullet bullets[MAX_BULLETS] = { 0 };

    // Enemies
    Enemy enemies[MAX_ENEMIES] = { 0 };
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = 50 + SimpleRand(0, screenWidth - 100);
        enemies[i].y = 50 + SimpleRand(0, 200);
        enemies[i].active = true;
    }

    bool gameOver = false;
    bool startScreen = true;

    while (!WindowShouldClose()) {

        // --- Start Screen ---
        if (startScreen) {
            if (IsKeyPressed(KEY_ENTER)) startScreen = false;

            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("SUPER COOL SPACE SHOOTER", 120, 200, 40, SKYBLUE);
            DrawText("Press ENTER to Start", 250, 300, 30, LIGHTGRAY);
            EndDrawing();
            continue;
        }

        // --- Game Over ---
        if (gameOver) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER", 250, 250, 50, RED);
            DrawText(TextFormat("Score: %d", score), 280, 320, 40, GREEN);
            DrawText("Press R to Restart", 230, 380, 30, WHITE);
            EndDrawing();

            if (IsKeyPressed(KEY_R)) {
                // Reset game
                playerX = screenWidth / 2.0f;
                playerY = screenHeight - 50;
                lives = 3;
                score = 0;
                gameOver = false;

                for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    enemies[i].x = 50 + SimpleRand(0, screenWidth - 100);
                    enemies[i].y = 50 + SimpleRand(0, 200);
                    enemies[i].active = true;
                }
            }
            continue;
        }

        // --- Input & Player Movement ---
        if (IsKeyDown(KEY_LEFT) && playerX > 20) playerX -= playerSpeed;
        if (IsKeyDown(KEY_RIGHT) && playerX < screenWidth - 20) playerX += playerSpeed;
        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].x = playerX;
                    bullets[i].y = playerY - 20;
                    bullets[i].active = true;
                    break;
                }
            }
        }

        // --- Update Bullets ---
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y -= 10;
                if (bullets[i].y < 0) bullets[i].active = false;
            }
        }

        // --- Update Enemies ---
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                enemies[i].y += 1.0f;
                if (enemies[i].y > screenHeight) {
                    enemies[i].y = 0;
                    enemies[i].x = 50 + SimpleRand(0, screenWidth - 100);
                    lives--;
                    if (lives <= 0) gameOver = true;
                }
            }
        }

        // --- Collision Detection ---
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active) {
                        float dx = bullets[i].x - enemies[j].x;
                        float dy = bullets[i].y - enemies[j].y;
                        float distance = dx * dx + dy * dy;
                        if (distance < 625) { // 25^2 radius collision
                            bullets[i].active = false;
                            enemies[j].active = false;
                            score += 10;
                        }
                    }
                }
            }
        }

        // --- Respawn Enemies ---
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) {
                enemies[i].x = 50 + SimpleRand(0, screenWidth - 100);
                enemies[i].y = 50;
                enemies[i].active = true;
            }
        }

        // --- Draw ---
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw player
        DrawPlayerShip(playerX, playerY);

        // Draw bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) DrawCircle((int)bullets[i].x, (int)bullets[i].y, 5, YELLOW);
        }

        // Draw enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) DrawEnemyShip(enemies[i].x, enemies[i].y);
        }

        // Draw HUD
        DrawText(TextFormat("Lives: %d", lives), 10, 10, 20, GREEN);
        DrawText(TextFormat("Score: %d", score), 10, 40, 20, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
