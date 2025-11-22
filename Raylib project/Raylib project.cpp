#include <cstdlib>
#include <ctime>
#include<raylib.h>  
using namespace std;



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
	int ShipW = WindowWidth / 2; //750/2=375; almost center of window
	int ShipH = WindowHieght - 60; //700-60=640; near to bottom of window
	int ShipWidth = 40;
	int ShipHieght = 50;
	int ShipSpeed = 5; //much fast
	int ShipALive = 5; //health of player(lives)
	const int MaxHealth = 5; //max health of player(it will remain same to the end of the code)



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


	while (WindowShouldClose() == false)
    {
		//again using function: will get detected if escape key is used or close icon
		//game will be closed if it turns true


		if (WaitToFire > 0)
        {
			WaitToFire--;

		}


		if (IsKeyDown(KEY_SPACE) && WaitToFire == 0)
        {
			
			
			//iskeyfunction; represesnts continuous action
			//key pressed + ready to fire(space ship)

			int BulletIndexForLoop = 0;
			while (BulletIndexForLoop < MAX_BULLETS)//maxbullets are 15;
			{

				if (!BulletActive[BulletIndexForLoop])//indirectingly; bullet is active=false
				{

					BulletActive[BulletIndexForLoop] = 1;//verifying bullet is flying in the air
					//now for position check;
					BulletPositionX[BulletIndexForLoop] = ShipWidth; //horizontal fire
					BulletPositionY[BulletIndexForLoop] = ShipHieght - 21;//will fire a bit
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



		BeginDrawing(); //will create a black screen
		ClearBackground(grey);//after clearing bg will be grey



		// Now loop first part; space ship craetion
		DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE);//main body
		DrawCircle(ShipW, ShipH - 5, 7, BLUE);//center or cockpit,with 7 asradius,others-positon
		DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE);//wing 1(left)
		DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE);//wing2(right;-ve coordinate)
		DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE);//engine fume;left
		DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE);//engine fume; right



		int DrawBullets = 0;
		while (DrawBullets < MAX_BULLETS)
			//this loop will eal with the graphics of bullets
		{

			if (BulletActive[DrawBullets])
				DrawCircle(BulletPositionX[DrawBullets], BulletPositionY[DrawBullets], 5, YELLOW);
			DrawBullets++;

		}


		int DrawingOfEnemyShips = 0;//loop variable
		while (DrawingOfEnemyShips < MaxEnemies)
			//dealing with enemies graphics
		{


			DrawRectangle(EnemyShipW - 18, EnemyShipH - 12, 36, 24, RED);
			DrawCircle(EnemyShipW, EnemyShipH - 3, 8, YELLOW);
			DrawCircle(EnemyShipW - 15, EnemyShipH - 15, 6, MAROON);
			DrawCircle(EnemyShipW + 15, EnemyShipH - 15, 6, MAROON);
			DrawCircle(EnemyShipW - 25, EnemyShipH + 5, 7, MAROON);
			DrawCircle(EnemyShipW + 25, EnemyShipH + 5, 7, MAROON);
			DrawCircle(EnemyShipW - 8, EnemyShipH + 16, 6, ORANGE);
			DrawCircle(EnemyShipW + 8, EnemyShipH + 16, 6, ORANGE);


			EnemyShipW += EnemyShipSpeed;

			if (EnemyShipH > WindowHieght)   // if enemy goes below the screen
			{
				EnemyShipH = -50;   // reset above the window
				EnemyShipW = GetRandomValue(50, WindowWidth - 50);
				// random new X position for variety
			}


			if (EnemyShipW < 20) EnemyShipW = 20;                     // left edge
			if (EnemyShipW > WindowWidth - 20) EnemyShipW = WindowWidth - 20; // right edge

			
			DrawingOfEnemyShips++;
		}



		EndDrawing();   //will end the black screen
	}


	//the first thing we will do with the while loop is to check the events 
	//which are going to happen in the game 
	CloseWindow();
}

		


		
