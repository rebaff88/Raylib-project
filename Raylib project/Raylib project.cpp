#include <cstdlib>
#include <ctime>
#include <raylib.h>  
#include <random> 
using namespace std;
//you are going to view our final programming fundamentals group project

void DemonstrateGraphics()
{
    Color grey = { 8, 4, 35, 255 };
    //here we have created a color variable using the structure Color,this will showcase
    // grey color in the backgound.

    int WindowWidth = 1100;
    int WindowHieght = 900;
    //here we have declaraed the first two variables now these two are actually defining 
    // the total frame size which will be shown at the time of playing, widht will be declared more 
    //the height so by that it will be more presentable

    InitWindow(WindowWidth, WindowHieght, "Welcome, space shooter");
    //initializing the game window(with help of a (in) built function)

    SetTargetFPS(50);
    //setting the frame rate of the game to 50 fps (speed)
    //loop will run 50 times per second

    //for space ship 
    int ShipW = WindowWidth / 2; //almost center of window
    int ShipH = WindowHieght - 60; //near to bottom of window
    int ShipWidth = 40;
    int ShipHieght = 50;
    int ShipSpeed = 5; //much fast
    int ShipALive = 5; //health of player(lives)
    const int MaxHealth = 5; //max health of player(it will remain same to the end of the code)

    //now i am going for bullets:
    const int MaximumNumOfBullets = 15;//max bullets fire in frame window at a time
    int BulletPositionX[MaximumNumOfBullets];//horizontal postion of bullet upgrading
    int BulletPositionY[MaximumNumOfBullets];//vertical position upgradation
    bool BulletActive[MaximumNumOfBullets];//bullet is moving or not (changed from int to bool for clarity)
    int BulletInitializedIndex = 0;//a variable for loop to be targeted
    int BulletSpeed = 9;
    int WaitToFire = 0;//when the bullet will start to be fired
    int WaitToFireTime = 10;//frames to when the next bullet is fired[FAST SPEED]
    int RadiusOfTheBullet = 5;

    while (BulletInitializedIndex < MaximumNumOfBullets)
    {
        BulletActive[BulletInitializedIndex] = false; // Set to false (inactive)
        BulletPositionX[BulletInitializedIndex] = 0;
        BulletPositionY[BulletInitializedIndex] = 0;
        BulletInitializedIndex++;
    }

    int starIndex = 0;//creating some moving stars lol
    const int NumberOfStars = 200;
    int StarPositionX[NumberOfStars];//horizontal position
    int StarPositionY[NumberOfStars];//vertical

    // Initialize star positions once (so stars have valid starting coordinates)
    starIndex = 0;
    while (starIndex < NumberOfStars)
    {
        StarPositionX[starIndex] = rand() % WindowWidth;
        StarPositionY[starIndex] = rand() % WindowHieght;
        starIndex++;
    }

    //here i have initialized planats lol'
    const int NumberOfPlanetsGoingToFall = 8;//the number of planets which are going to fall in the window frame
    int PlanetPositionX[NumberOfPlanetsGoingToFall] = { 100, 400, 160, 206, 530, 605, 60, 76 };
    int PlanetPositionY[NumberOfPlanetsGoingToFall] = { -100, -200, -150, -150, -250, -300, -100, 345 };
    int PlanetRadius[NumberOfPlanetsGoingToFall] = { 30, 50, 38, 45, 35, 26, 14, 10 };//radius of the planets
    int PlanetFallingSpeed[NumberOfPlanetsGoingToFall] = { 2, 4, 1, 3, 2, 6, 5, 6 };
    Color PlanetFirstColor[NumberOfPlanetsGoingToFall] = { BLUE, RED, GOLD, GREEN, PURPLE, ORANGE, PINK, BROWN };
    Color PlanetSecondColors[NumberOfPlanetsGoingToFall] = { DARKBLUE, MAROON, ORANGE, DARKGREEN, MAGENTA, BROWN, GOLD, ORANGE };
    Color PlanetThirdColors[NumberOfPlanetsGoingToFall] = { BLUE, PINK, YELLOW, LIME, VIOLET, BEIGE, YELLOW, YELLOW };

    const int SUNPlanet = 1;
    int SUNPlanetPositionX[SUNPlanet] = { 350 };
    int SUNPlanetPositionY[SUNPlanet] = { -500 };
    int SUNPlanetRadius[SUNPlanet] = { 60 };
    Color SUNPlanetFirstColor[SUNPlanet] = { YELLOW };
    Color SUNPlanetSecondColors[SUNPlanet] = { ORANGE };
    Color SUNPlanetThirdColors[SUNPlanet] = { GOLD };

    bool TheGameHasStarted = false; //the game has not started yet

    // --- Enemy variables ---
    const int MaxEnemies = 10;
    int EnemyPosX[MaxEnemies];
    int EnemyPosY[MaxEnemies];
    int EnemySpeed[MaxEnemies];
    bool EnemyActive[MaxEnemies];

    int Score = 0;
    bool GameOver = false;

    // Initialize enemies
    for (int i = 0; i < MaxEnemies; i++) {
        EnemyActive[i] = false;
        EnemyPosX[i] = rand() % (WindowWidth - 40);
        EnemyPosY[i] = -rand() % 300; // start above the screen
        EnemySpeed[i] = 2 + rand() % 3; // speed 2-4
    }

    // --- Main start ---
    while (!TheGameHasStarted && !WindowShouldClose())//the condition is defying
    {
        BeginDrawing();
        ClearBackground(grey);

        // Draw stars
        {
            int starIndex = 0;
            while (starIndex < NumberOfStars)
            {
                DrawPixel(StarPositionX[starIndex], StarPositionY[starIndex], WHITE);
                StarPositionY[starIndex] = StarPositionY[starIndex] + 1;
                if (StarPositionY[starIndex] > WindowHieght)
                {
                    StarPositionY[starIndex] = 0;
                    StarPositionX[starIndex] = rand() % WindowWidth;
                }
                starIndex = starIndex + 1;
            }
        }

        // Draw planets
        for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++)
        {
            DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop], PlanetFirstColor[PlanetForLoop]);
            DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.7, PlanetSecondColors[PlanetForLoop]);
            DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.4, PlanetThirdColors[PlanetForLoop]);
            PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop];

            if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)
                PlanetPositionY[PlanetForLoop] = -PlanetRadius[PlanetForLoop] - 50;
        }

        DrawText("Welcome!", WindowWidth / 2 - 180, WindowHieght / 2 - 80, 65, YELLOW);
        DrawText("SpaceShooter..!", WindowWidth / 2 - 150, WindowHieght / 2 + 20, 50, SKYBLUE);
        DrawText("Press Enter 2 Enter", WindowWidth / 2 - 200, WindowHieght / 2 + 70, 40, WHITE);
        DrawText("USE Arrow Keys To move & Space Key to Sh**t!!", WindowWidth / 2 - 160, WindowHieght / 2 - 20, 40, YELLOW);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            TheGameHasStarted = true; //the bool will be true and the game will begin
    }

    // --- Main game loop ---
    while (WindowShouldClose() == false)
    {
        if (!GameOver) {
            // Spawn enemies if less than MaxEnemies active
            for (int i = 0; i < MaxEnemies; i++) {
                if (!EnemyActive[i]) {
                    EnemyActive[i] = true;
                    EnemyPosX[i] = rand() % (WindowWidth - 40);
                    EnemyPosY[i] = -50; // start above the screen
                    EnemySpeed[i] = 2 + rand() % 3;
                }
            }

            // Move enemies and check collisions
            for (int i = 0; i < MaxEnemies; i++) {
                if (EnemyActive[i]) {
                    EnemyPosY[i] += EnemySpeed[i];

                    // Check collision with ship
                    if (EnemyPosY[i] + 30 > ShipH && EnemyPosY[i] < ShipH + 50 &&
                        EnemyPosX[i] + 30 > ShipW && EnemyPosX[i] < ShipW + ShipWidth) {
                        GameOver = true; // enemy hit the ship
                    }

                    // Check collision with bullets
                    for (int j = 0; j < MaximumNumOfBullets; j++) {
                        if (BulletActive[j]) {
                            if (BulletPositionY[j] - 5 < EnemyPosY[i] + 15 && BulletPositionY[j] + 5 > EnemyPosY[i] &&
                                BulletPositionX[j] > EnemyPosX[i] && BulletPositionX[j] < EnemyPosX[i] + 30) {
                                // Enemy hit
                                EnemyActive[i] = false;
                                BulletActive[j] = false;
                                Score += 10; // increase score
                            }
                        }
                    }

                    // Remove enemies that go out of screen
                    if (EnemyPosY[i] > WindowHieght + 50) {
                        EnemyActive[i] = false;
                    }
                }
            }

            // Draw enemies
            for (int i = 0; i < MaxEnemies; i++) {
                if (EnemyActive[i]) {
                    DrawCircle(EnemyPosX[i], EnemyPosY[i], 15, RED);
                }
            }

            // Display score
            DrawText(TextFormat("Score: %d", Score), 20, 20, 30, WHITE);
        }

        // Draw ship
        DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE); // main body
        DrawCircle(ShipW, ShipH - 5, 7, BLUE); // cockpit
        DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE); // wing left
        DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE); // wing right
        DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE); // engine left
        DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE); // engine right

        // Bullets
        if (IsKeyDown(KEY_SPACE) && WaitToFire >= WaitToFireTime)
        {
            for (int i = 0; i < MaximumNumOfBullets; i++)
            {
                if (!BulletActive[i])
                {
                    BulletPositionX[i] = ShipW; // center of ship
                    BulletPositionY[i] = ShipH;
                    BulletActive[i] = true;
                    WaitToFire = 0; // reset cooldown
                    break;
                }
            }
        }
        WaitToFire++;

        for (int i = 0; i < MaximumNumOfBullets; i++)
        {
            if (BulletActive[i])
            {
                BulletPositionY[i] -= BulletSpeed; // move up
                if (BulletPositionY[i] < 0)
                    BulletActive[i] = false;
            }
        }

        // Update star positions
        {
            int starIndex = 0;
            while (starIndex < NumberOfStars)
            {
                DrawPixel(StarPositionX[starIndex], StarPositionY[starIndex], WHITE);
                StarPositionY[starIndex] += 1;
                if (StarPositionY[starIndex] > WindowHieght)
                {
                    StarPositionY[starIndex] = 0;
                    StarPositionX[starIndex] = rand() % WindowWidth;
                }
                starIndex++;
            }
        }

        // Draw planets
        for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++)
        {
            DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop], PlanetFirstColor[PlanetForLoop]);
            DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.7, PlanetSecondColors[PlanetForLoop]);
            DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.4, PlanetThirdColors[PlanetForLoop]);
            PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop];

            if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)
                PlanetPositionY[PlanetForLoop] = -PlanetRadius[PlanetForLoop] - 50;
        }

        // Move planets
        for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++) {
            PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop];
            if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)
                PlanetPositionY[PlanetForLoop] = -PlanetRadius[PlanetForLoop] - 50;
        }

        // Ship movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            ShipW += ShipSpeed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            ShipW -= ShipSpeed;

        // Keep ship within bounds
        if (ShipW < 20) ShipW = 20;
        if (ShipW > WindowWidth - 20) ShipW = WindowWidth - 20;

        // --- Enemy logic ---
        if (!GameOver) {
            // Spawn enemies
            for (int i = 0; i < MaxEnemies; i++) {
                if (!EnemyActive[i]) {
                    EnemyActive[i] = true;
                    EnemyPosX[i] = rand() % (WindowWidth - 40);
                    EnemyPosY[i] = -50; // start above screen
                    EnemySpeed[i] = 2 + rand() % 3;
                }
            }

            // Move enemies and check collisions
            for (int i = 0; i < MaxEnemies; i++) {
                if (EnemyActive[i]) {
                    EnemyPosY[i] += EnemySpeed[i];

                    // Check collision with ship
                    if (EnemyPosY[i] + 15 > ShipH - 10 && EnemyPosY[i] - 15 < ShipH + 50 &&
                        EnemyPosX[i] + 15 > ShipW - 20 && EnemyPosX[i] - 15 < ShipW + ShipWidth) {
                        GameOver = true; // enemy hit the ship
                    }

                    // Check collision with bullets
                    for (int j = 0; j < MaximumNumOfBullets; j++) {
                        if (BulletActive[j]) {
                            if (BulletPositionY[j] - 5 < EnemyPosY[i] + 15 && BulletPositionY[j] + 5 > EnemyPosY[i] - 15 &&
                                BulletPositionX[j] > EnemyPosX[i] - 15 && BulletPositionX[j] < EnemyPosX[i] + 15) {
                                // Enemy hit
                                EnemyActive[i] = false;
                                BulletActive[j] = false;
                                Score += 10;
                            }
                        }
                    }

                    // Remove enemies out of screen
                    if (EnemyPosY[i] > WindowHieght + 50) {
                        EnemyActive[i] = false;
                    }
                }
            }

            // Draw enemies
            for (int i = 0; i < MaxEnemies; i++) {
                if (EnemyActive[i]) {
                    DrawCircle(EnemyPosX[i], EnemyPosY[i], 15, RED);
                }
            }

            // Draw score
            DrawText(TextFormat("Score: %d", Score), 20, 20, 30, WHITE);
        }

        // Draw bullets
        for (int i = 0; i < MaximumNumOfBullets; i++)
        {
            if (BulletActive[i])
            {
                DrawCircle(BulletPositionX[i], BulletPositionY[i], RadiusOfTheBullet, WHITE);
            }
        }

        // Game Over display
        if (GameOver)
        {
            DrawText("GAME OVER!", WindowWidth / 2 - 150, WindowHieght / 2 - 20, 50, RED);
            DrawText("Press ENTER to Restart", WindowWidth / 2 - 180, WindowHieght / 2 + 40, 30, WHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
                // Restart game
                Score = 0;
                GameOver = false;
                for (int i = 0; i < MaxEnemies; i++) {
                    EnemyActive[i] = false;
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}

int main()
{
    DemonstrateGraphics();
}