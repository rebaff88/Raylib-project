#include <cstdlib>
#include <ctime>
#include <raylib.h>  

using namespace std;

void DemonstrateGraphics()
{
    Color grey = { 8, 4, 35, 255 };
    int WindowWidth = 1100;
    int WindowHieght = 900;

    InitWindow(WindowWidth, WindowHieght, "Welcome, space shooter");
    SetTargetFPS(50);

    // Seed random generator
    srand(time(0));

    // Player ship properties
    int ShipW = WindowWidth / 2; // Centered
    int ShipH = WindowHieght - 60;
    const int ShipWidth = 40;
    const int ShipHieght = 50;
    const int ShipSpeed = 5;

    int PlayerHealth = 5; // Player starts with 5 lives
    bool GameOver = false;

    // Bullets
    const int MaximumNumOfBullets = 15;
    int BulletPositionX[MaximumNumOfBullets];
    int BulletPositionY[MaximumNumOfBullets];
    bool BulletActive[MaximumNumOfBullets];

    int WaitToFire = 0;
    const int WaitToFireTime = 10;
    const int BulletSpeed = 9;
    const int RadiusOfTheBullet = 5;

    for (int i = 0; i < MaximumNumOfBullets; i++)
    {
        BulletActive[i] = false;
        BulletPositionX[i] = 0;
        BulletPositionY[i] = 0;
    }

    // Stars
    const int NumberOfStars = 200;
    int StarPositionX[NumberOfStars];
    int StarPositionY[NumberOfStars];

    for (int i = 0; i < NumberOfStars; i++)
    {
        StarPositionX[i] = rand() % WindowWidth;
        StarPositionY[i] = rand() % WindowHieght;
    }

    // Planets
    const int NumberOfPlanets = 8;
    int PlanetPositionX[NumberOfPlanets] = { 100, 400, 160, 206, 530, 605, 60, 76 };
    int PlanetPositionY[NumberOfPlanets] = { -100, -200, -150, -150, -250, -300, -100, 345 };
    int PlanetRadius[NumberOfPlanets] = { 30, 50, 38, 45, 35, 26, 14, 10 };
    int PlanetSpeed[NumberOfPlanets] = { 2, 4, 1, 3, 2, 6, 5, 6 };
    Color PlanetColors1[NumberOfPlanets] = { BLUE, RED, GOLD, GREEN, PURPLE, ORANGE, PINK, BROWN };
    Color PlanetColors2[NumberOfPlanets] = { DARKBLUE, MAROON, ORANGE, DARKGREEN, MAGENTA, BROWN, GOLD, ORANGE };
    Color PlanetColors3[NumberOfPlanets] = { BLUE, PINK, YELLOW, LIME, VIOLET, BEIGE, YELLOW, YELLOW };

    // Sun
    const int SunCount = 1;
    int SunX[SunCount] = { 350 };
    int SunY[SunCount] = { -500 };
    int SunRadius[SunCount] = { 60 };
    Color SunColors1[SunCount] = { YELLOW };
    Color SunColors2[SunCount] = { ORANGE };
    Color SunColors3[SunCount] = { GOLD };

    // Enemies
    const int MaxEnemies = 5;
    int EnemyX[MaxEnemies];
    int EnemyY[MaxEnemies];
    int EnemySpeed[MaxEnemies];

    for (int i = 0; i < MaxEnemies; i++)
    {
        EnemyX[i] = GetRandomValue(50, WindowWidth - 50);
        EnemyY[i] = GetRandomValue(-300, -50);
        EnemySpeed[i] = GetRandomValue(1, 3);
    }

    bool StartGame = false;

    // Initial start screen
    while (!StartGame && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);
        DrawText("Welcome!", WindowWidth / 2 - 180, WindowHieght / 2 - 80, 65, YELLOW);
        DrawText("SpaceShooter..!", WindowWidth / 2 - 150, WindowHieght / 2 + 20, 50, SKYBLUE);
        DrawText("Press Enter 2 Enter", WindowWidth / 2 - 200, WindowHieght / 2 + 70, 40, WHITE);
        DrawText("USE Arrow Keys To move & Space Key to Sh**t!!", WindowWidth / 2 - 160, WindowHieght / 2 - 20, 40, YELLOW);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            StartGame = true;
    }

    // Main game loop
    while (!WindowShouldClose())
    {
        if (PlayerHealth <= 0)
        {
            // Game over
            BeginDrawing();
            ClearBackground(grey);
            DrawText("GAME OVER!", WindowWidth / 2 - 150, WindowHieght / 2 - 20, 50, RED);
            EndDrawing();
            // Wait for user to close window
            continue;
        }

        // Input for ship movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            ShipW += ShipSpeed;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            ShipW -= ShipSpeed;
        }
        // Keep ship within bounds
        if (ShipW < 0) ShipW = 0;
        if (ShipW + ShipWidth > WindowWidth) ShipW = WindowWidth - ShipWidth;

        // Shooting bullets
        if (IsKeyDown(KEY_SPACE) && WaitToFire >= WaitToFireTime)
        {
            for (int i = 0; i < MaximumNumOfBullets; i++)
            {
                if (!BulletActive[i])
                {
                    BulletPositionX[i] = ShipW + ShipWidth / 2;
                    BulletPositionY[i] = ShipH;
                    BulletActive[i] = true;
                    WaitToFire = 0;
                    break;
                }
            }
        }
        WaitToFire++;

        // Update bullets
        for (int i = 0; i < MaximumNumOfBullets; i++)
        {
            if (BulletActive[i])
            {
                BulletPositionY[i] -= BulletSpeed;
                if (BulletPositionY[i] < 0)
                    BulletActive[i] = false;
            }
        }

        // Update enemies
        for (int i = 0; i < MaxEnemies; i++)
        {
            EnemyY[i] += EnemySpeed[i];

            if (EnemyY[i] > WindowHieght + 50)
            {
                EnemyY[i] = -50;
                EnemyX[i] = GetRandomValue(50, WindowWidth - 50);
            }

            // Draw enemy ship
            DrawRectangle(EnemyX[i] - 18, EnemyY[i] - 12, 36, 24, MAROON);
            DrawCircle(EnemyX[i], EnemyY[i] - 3, 8, YELLOW);
            DrawCircle(EnemyX[i] - 15, EnemyY[i] - 15, 6, MAROON);
            DrawCircle(EnemyX[i] + 15, EnemyY[i] - 15, 6, MAROON);
            DrawCircle(EnemyX[i] - 25, EnemyY[i] + 5, 7, MAROON);
            DrawCircle(EnemyX[i] + 25, EnemyY[i] + 5, 7, MAROON);
            DrawCircle(EnemyX[i] - 8, EnemyY[i] + 16, 6, ORANGE);
            DrawCircle(EnemyX[i] + 8, EnemyY[i] + 16, 6, ORANGE);

            // Check collision with player
            if (EnemyY[i] + 12 > ShipH - 10 && EnemyY[i] - 12 < ShipH + ShipHieght)
            {
                if (EnemyX[i] + 18 > ShipW && EnemyX[i] - 18 < ShipW + ShipWidth)
                {
                    PlayerHealth--;
                    EnemyY[i] = -50; // respawn enemy
                }
            }

            // Check collision with bullets
            for (int j = 0; j < MaximumNumOfBullets; j++)
            {
                if (BulletActive[j])
                {
                    if (abs(BulletPositionX[j] - EnemyX[i]) < 20 && abs(BulletPositionY[j] - EnemyY[i]) < 20)
                    {
                        BulletActive[j] = false;
                        EnemyY[i] = -50; // respawn enemy
                        break;
                    }
                }
            }
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(grey);

        // Draw stars
        for (int i = 0; i < NumberOfStars; i++)
        {
            DrawPixel(StarPositionX[i], StarPositionY[i], WHITE);
            StarPositionY[i] += 1;
            if (StarPositionY[i] > WindowHieght)
            {
                StarPositionY[i] = 0;
                StarPositionX[i] = rand() % WindowWidth;
            }
        }

        // Draw planets
        for (int i = 0; i < NumberOfPlanets; i++)
        {
            DrawCircle(PlanetPositionX[i], PlanetPositionY[i], PlanetRadius[i], PlanetColors1[i]);
            DrawCircle(PlanetPositionX[i], PlanetPositionY[i], PlanetRadius[i] * 0.7, PlanetColors2[i]);
            DrawCircle(PlanetPositionX[i], PlanetPositionY[i], PlanetRadius[i] * 0.4, PlanetColors3[i]);
            PlanetPositionY[i] += PlanetSpeed[i];
            if (PlanetPositionY[i] - PlanetRadius[i] > WindowHieght)
                PlanetPositionY[i] = -PlanetRadius[i] - 50;
        }

        // Draw player ship
        DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE);
        DrawCircle(ShipW, ShipH - 5, 7, BLUE);
        DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE);
        DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE);
        DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE);
        DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE);

        // Draw bullets
        for (int i = 0; i < MaximumNumOfBullets; i++)
        {
            if (BulletActive[i])
                DrawCircle(BulletPositionX[i], BulletPositionY[i], RadiusOfTheBullet, WHITE);
        }

        // Draw health
        DrawText(TextFormat("Health: %d", PlayerHealth), 10, 10, 20, WHITE);

        // Draw game over message if health is zero
        if (PlayerHealth <= 0)
        {
            DrawText("GAME OVER!", WindowWidth / 2 - 150, WindowHieght / 2 - 20, 50, RED);
        }

        EndDrawing();
    }

    CloseWindow();
}

int main()
{
    DemonstrateGraphics();
}