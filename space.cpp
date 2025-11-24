#include <ctime>
#include <raylib.h>  
#include <iostream>
using namespace std;

//you are going to view our final programming fundamentals group project

int main()
{
    Color grey = { 22, 18, 27, 255 };
    //here we have created a color variable using the structure Color,this will showcase
    // grey color in the backgound.

    int WindowWidth = 750;
    int WindowHieght = 700;
    //here we have declaraed the first two variables now these two are actually defining 
    // the total frame size which will be shown at the time of playing, widht will be declared more 
    //the height so by that it will be more presentable

    InitWindow(WindowWidth, WindowHieght, "Welcome, space shooter");
    //initializing the game window(with help of a (in) built function)

    SetTargetFPS(60);
    //setting the frame rate of the game to 60 fps (speed)
    //loop will run 60 times per second


    //for space ship 
    int ShipW = WindowWidth / 2; //375; almost center of window
    int ShipH = WindowHieght - 60; //near bottom of window
    int ShipWidth = 40;
    int ShipHieght = 50;
    int ShipSpeed = 5; //much fast
    // int ShipALive = 5; //health of player(lives)  <-- REMOVE THIS
    // const int MaxHealth = 5; //max health of player(it will remain same to the end of the code) <-- REMOVE THIS

    //multiple enemies
    const int MaxEnemies = 5; //defining a constant variable for maximum enemies at atime on window
    int EnemyPositionX[MaxEnemies];//horizontal position
    int EnemyPostionY[MaxEnemies];//vertical postion
    int EnemyShipSpeedArr[MaxEnemies]; // speed of each enemy ship
    //for the ship of the enemies
    int EnemyShipW = WindowWidth / 2; //750/2=375; again almost center of window
    int EnemyShipH = 60; //near to top of window
    int EnemyShipSpeed = 2; //medium speed of the enemy ship

    const int MAX_BULLETS = 15;//max bullets fire in frame window at a time
    int BulletPositionX[MAX_BULLETS];//horizontal postion of bullet upgrading
    int BulletPositionY[MAX_BULLETS];//vertical position upgradation
    int BulletActive[MAX_BULLETS];//bullet is moving or not 
    int BulletInitializedIndex = 0;//a variable for loop to be targeted
    int BulletSpeed = 9;
    int WaitToFire = 0;//when the bullet will start to be fired
    int WaitToFireTime = 10;//frames to when the next bullet is fired      [FAST SPEED]

    while (BulletInitializedIndex < MAX_BULLETS)
    {
        BulletActive[BulletInitializedIndex] = 0;
        BulletPositionX[BulletInitializedIndex] = 0;
        BulletPositionY[BulletInitializedIndex] = 0;
        BulletInitializedIndex++;
    }

    int i = 0;
    while (i < MaxEnemies)    //respawning of enemies
    {
        EnemyPositionX[i] = GetRandomValue(50, WindowWidth - 50); //it is the safe zone
        //otherwise the enemy spaceships will either get out of the screen or can be spawned at 
        //left or right side of the window
        EnemyPostionY[i] = GetRandomValue(-300, -60);//verticaly spawning
        EnemyShipSpeedArr[i] = GetRandomValue(2, 4);//speed is fluctuating some will be very fast
        //some will be moderate
        i++;
    }

    int score = 0;//score for the player ship will always start from 0 and will increase
    //as the game will proceed.

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

    bool TheGameHasStarted = false; //the game has not started yet
    bool gameOver = false; // Declare gameOver flag
    while (!TheGameHasStarted && !WindowShouldClose())//the condition is defying
        //ie the game is started
    {
        BeginDrawing();
        ClearBackground(grey);

        // Draw and update stars (simple downward movement)
        {
            int starIndex = 0;
            while (starIndex < NumberOfStars)
            {
                DrawPixel(StarPositionX[starIndex], StarPositionY[starIndex], WHITE);
                //using a raylib function and pasing parameters;

                // Move star down by 1 pixel each frame
                StarPositionY[starIndex] = StarPositionY[starIndex] + 1;

                if (StarPositionY[starIndex] > WindowHieght)//out of screen. star has gone beyond 
                    //the window(downwards) ie hieght
                {
                    StarPositionY[starIndex] = 0;//again the value will go to 0
                    //regenerating a star
                    StarPositionX[starIndex] = rand() % WindowWidth;
                }

                starIndex = starIndex + 1; // respawning next star
            }
        }

        DrawText("Welcome!", WindowWidth / 2 - 180, WindowHieght / 2 - 80, 65, YELLOW);
        DrawText("SpaceShooter..!", WindowWidth / 2 - 150, WindowHieght / 2 + 20, 50, SKYBLUE);
        DrawText("Press Enter 2 Enter", WindowWidth / 2 - 200, WindowHieght / 2 + 70, 40, WHITE);
        DrawText("USE Arrow Keys To move & Space Key to Sh**t!!", WindowWidth / 2 - 160, WindowHieght / 2 - 20, 40, YELLOW);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            TheGameHasStarted = true; //the bool will be true and the game will begin
    }

    while (WindowShouldClose() == false && !gameOver)
    {
        //again using function: will get detected if escape key is used or close icon
        //game will be closed if it turns true

        if (WaitToFire > 0)
        {
            WaitToFire--;
        }

        // Fire bullet with space key
        if (IsKeyDown(KEY_SPACE) && WaitToFire == 0)
        {
            int BulletIndexForLoop = 0;
            while (BulletIndexForLoop < MAX_BULLETS)//maxbullets are 15;
            {
                if (!BulletActive[BulletIndexForLoop])//indirectingly; bullet is active=false
                {
                    BulletActive[BulletIndexForLoop] = 1;//verifying bullet is flying in the air
                    //now for position check;
                    BulletPositionX[BulletIndexForLoop] = ShipW; //corrected from ShipWidth
                    BulletPositionY[BulletIndexForLoop] = ShipH - 21;//will fire a bit above the ship;
                    //above the ship;
                    WaitToFire = WaitToFireTime;//the period for which the player fires a bullet to 
                    //the firing of the next bullet(reset) 
                    break;
                }
                BulletIndexForLoop++;
            }
        }

        if (IsKeyDown(KEY_LEFT))//using a raylib funtion to check if left key is pressed
            ShipW -= ShipSpeed;//the position of the ship will get updated to left side
        if (IsKeyDown(KEY_RIGHT))//checking when the right arrow key is pressed
            ShipW += ShipSpeed;//increment as to right>shipwidth

        //for stopping the ship to not leave the window to extreme right or left
        if (ShipW < 20) ShipW = 20; //left corner
        if (ShipW > WindowWidth - 20) ShipW = WindowWidth - 20; //right corner

        // Start drawing the game frame
        BeginDrawing();
        ClearBackground(grey);

        // Draw the spaceship
        DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE);
        DrawCircle(ShipW, ShipH - 5, 7, BLUE);
        DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE);
        DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE);
        DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE);
        DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE);

        // Draw bullets
        int DrawBullets = 0; // Declare once here
        DrawBullets = 0; // Reset to 0 before drawing
        while (DrawBullets < MAX_BULLETS)
        {
            if (BulletActive[DrawBullets])
                DrawCircle(BulletPositionX[DrawBullets], BulletPositionY[DrawBullets], 5, YELLOW);
            DrawBullets++;
        }

        // Draw enemies and update their positions
        int DrawingOfEnemyShips = 0;
        while (DrawingOfEnemyShips < MaxEnemies)
        {
            // Draw enemy ship
            DrawRectangle(EnemyPositionX[DrawingOfEnemyShips] - 18, EnemyPostionY[DrawingOfEnemyShips] - 12, 36, 24, MAROON);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips], EnemyPostionY[DrawingOfEnemyShips] - 3, 8, YELLOW);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips] - 15, EnemyPostionY[DrawingOfEnemyShips] - 15, 6, MAROON);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips] + 15, EnemyPostionY[DrawingOfEnemyShips] - 15, 6, MAROON);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips] - 25, EnemyPostionY[DrawingOfEnemyShips] + 5, 7, MAROON);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips] + 25, EnemyPostionY[DrawingOfEnemyShips] + 5, 7, MAROON);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips] - 8, EnemyPostionY[DrawingOfEnemyShips] + 16, 6, ORANGE);
            DrawCircle(EnemyPositionX[DrawingOfEnemyShips] + 8, EnemyPostionY[DrawingOfEnemyShips] + 16, 6, ORANGE);

            // Update enemy position
            EnemyPostionY[DrawingOfEnemyShips] += EnemyShipSpeedArr[DrawingOfEnemyShips];

            // Respawn enemy if it goes below the window
            if (EnemyPostionY[DrawingOfEnemyShips] > WindowHieght + 50) {
                EnemyPostionY[DrawingOfEnemyShips] = -50; // reset above the window
                EnemyPositionX[DrawingOfEnemyShips] = GetRandomValue(50, WindowWidth - 50);
            }

            // Keep enemy within horizontal bounds
            if (EnemyPositionX[DrawingOfEnemyShips] < 20) EnemyPositionX[DrawingOfEnemyShips] = 20;
            if (EnemyPositionX[DrawingOfEnemyShips] > WindowWidth - 20) EnemyPositionX[DrawingOfEnemyShips] = WindowWidth - 20;

            // **Collision detection between enemy and spaceship (Game Over)**
            if (EnemyPostionY[DrawingOfEnemyShips] > ShipH - 50 && EnemyPostionY[DrawingOfEnemyShips] < ShipH + 50)
            {
                if (abs(EnemyPositionX[DrawingOfEnemyShips] - ShipW) < 30)
                {
                    // Collision detected - game over
                    // Instead of just respawning, we set game over to true
                    // (Note: the main loop will handle game over)
                    gameOver = true;
                }
            }

            DrawingOfEnemyShips++;
        }

        // Check bullets collision with enemies
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (BulletActive[i])
            {
                for (int j = 0; j < MaxEnemies; j++)
                {
                    if (abs(BulletPositionX[i] - EnemyPositionX[j]) < 20 && abs(BulletPositionY[i] - EnemyPostionY[j]) < 20)
                    {
                        BulletActive[i] = 0;
                        EnemyPostionY[j] = -60; // respawn enemy
                        EnemyPositionX[j] = GetRandomValue(50, WindowWidth - 50);
                        score++;
                    }
                }
            }
        }

        // Drawing game over message if game over
        if (gameOver)
        {
            DrawText("Game Over!", WindowWidth / 2 - 150, WindowHieght / 2 - 20, 50, RED);
        }
        else
        {
            // Draw the spaceship
            DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE);
            DrawCircle(ShipW, ShipH - 5, 7, BLUE);
            DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE);
            DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE);
            DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE);
            DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE);

            // Draw bullets
            int DrawBullets = 0; // Declare once here
            DrawBullets = 0; // Reset to 0 before drawing
            while (DrawBullets < MAX_BULLETS)
            {
                if (BulletActive[DrawBullets])
                    DrawCircle(BulletPositionX[DrawBullets], BulletPositionY[DrawBullets], 5, YELLOW);
                DrawBullets++;
            }

            // Draw enemies
            int DrawingOfEnemyShips = 0;
            while (DrawingOfEnemyShips < MaxEnemies)
            {
                DrawRectangle(EnemyPositionX[DrawingOfEnemyShips] - 18, EnemyPostionY[DrawingOfEnemyShips] - 12, 36, 24, MAROON);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips], EnemyPostionY[DrawingOfEnemyShips] - 3, 8, YELLOW);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips] - 15, EnemyPostionY[DrawingOfEnemyShips] - 15, 6, MAROON);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips] + 15, EnemyPostionY[DrawingOfEnemyShips] - 15, 6, MAROON);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips] - 25, EnemyPostionY[DrawingOfEnemyShips] + 5, 7, MAROON);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips] + 25, EnemyPostionY[DrawingOfEnemyShips] + 5, 7, MAROON);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips] - 8, EnemyPostionY[DrawingOfEnemyShips] + 16, 6, ORANGE);
                DrawCircle(EnemyPositionX[DrawingOfEnemyShips] + 8, EnemyPostionY[DrawingOfEnemyShips] + 16, 6, ORANGE);
                DrawingOfEnemyShips++;
            }
        }

        EndDrawing();
    }

    //the first thing we will do with the while loop is to check the events 
    //which are going to happen in the game 
    CloseWindow();
}