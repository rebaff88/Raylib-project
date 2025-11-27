#include <cstdlib>
#include <ctime>
#include<raylib.h>  
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


	//here i have initialized planats lol'
	const int NumberOfPlanetsGoingToFall = 8;//the number of planets which are going to fall in the
	//window frame
	//now declaring the positions of the planets
	// i randomly tossed positions for the plaets 
	int PlanetPositionX[NumberOfPlanetsGoingToFall] = { 100, 400, 160, 206, 530, 605, 60, 76 };
	//horizontal
	int PlanetPositionY[NumberOfPlanetsGoingToFall] = { -100, -200, -150, -150, -250, -300, -100, 345 };
	//vertical positions
	//now i am going for the radius of the planets 
	int PlanetRadius[NumberOfPlanetsGoingToFall] = { 30, 50, 38, 45, 35, 26, 14, 10 };//radius of the
	//8 planets some are very big, medium and very small
	//now i am going for speed of the planets iam have folowed the same pattern(random)
	//now for speed and colors;
	int PlanetFallingSpeed[NumberOfPlanetsGoingToFall] = { 2, 4, 1, 3, 2, 6, 5, 6 };
	//as it will have three layesr so: 
	Color PlanetFirstColor[NumberOfPlanetsGoingToFall] = { BLUE, RED, GOLD, GREEN, PURPLE, ORANGE, PINK, BROWN };
	Color PlanetSecondColors[NumberOfPlanetsGoingToFall] = { DARKBLUE, MAROON, ORANGE, DARKGREEN, MAGENTA, BROWN, GOLD, ORANGE };
	Color PlanetThirdColors[NumberOfPlanetsGoingToFall] = { BLUE, PINK, YELLOW, LIME, VIOLET, BEIGE, YELLOW, YELLOW };


	const int SUNPlanet = 1;
	//for sun in the center
	int SUNPlanetPositionX[SUNPlanet] = { 350 };
	int SUNPlanetPositionY[SUNPlanet] = { -500 };
	int SUNPlanetRadius[SUNPlanet] = { 60 };
	Color SUNPlanetFirstColor[SUNPlanet] = { YELLOW };
	Color SUNPlanetSecondColors[SUNPlanet] = { ORANGE };
	Color SUNPlanetThirdColors[SUNPlanet] = { GOLD };



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



		//here i am going to use a for loop to draw the planets and make them fall
		for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++)
		{//for the first layer:
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop], PlanetFirstColor[PlanetForLoop]);

			//for the second layer
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.7, PlanetSecondColors[PlanetForLoop]);

			//for the third loop
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.4, PlanetThirdColors[PlanetForLoop]);


			PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop]; //as if the planets move down
			//wrds they will cover more distance vertically from the top lol

			if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)//of course it 
				//should be in the frame window ie hieght
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


	while (WindowShouldClose() == false)
	{
		//again using function: will get detected if escape key is used or close icon
		//game will be closed if it turns true


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


		// here i am going to repaste the code for planets i have made using a loop above: 
				//here i am going to use a for loop to draw the planets and make them fall
		for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++)
		{//for the first layer:
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop], PlanetFirstColor[PlanetForLoop]);

			//for the second layer
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.7, PlanetSecondColors[PlanetForLoop]);

			//for the third loop
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.4, PlanetThirdColors[PlanetForLoop]);


			PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop]; //as if the planets move down
			//wrds they will cover more distance vertically from the top lol

			if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)//of course it 
				//should be in the frame window ie hieght
				PlanetPositionY[PlanetForLoop] = -PlanetRadius[PlanetForLoop] - 50;
		}


		for (int SUNPlanetForLoop = 0; SUNPlanetForLoop < NumberOfPlanetsGoingToFall; SUNPlanetForLoop++)
		{//for the first layer:
			DrawCircle(PlanetPositionX[SUNPlanetForLoop], PlanetPositionY[SUNPlanetForLoop], PlanetRadius[SUNPlanetForLoop], PlanetFirstColor[SUNPlanetForLoop]);
			//for the second layer
			DrawCircle(PlanetPositionX[SUNPlanetForLoop], PlanetPositionY[SUNPlanetForLoop], PlanetRadius[SUNPlanetForLoop] * 0.7, PlanetSecondColors[SUNPlanetForLoop]);
			//for the third loop
			DrawCircle(PlanetPositionX[SUNPlanetForLoop], PlanetPositionY[SUNPlanetForLoop], PlanetRadius[SUNPlanetForLoop] * 0.4, PlanetThirdColors[SUNPlanetForLoop]);


			PlanetPositionY[SUNPlanetForLoop] += PlanetFallingSpeed[SUNPlanetForLoop]; //as if the planets move down
			//wrds they will cover more distance vertically from the top lol

			if (PlanetPositionY[SUNPlanetForLoop] - PlanetRadius[SUNPlanetForLoop] > WindowHieght)//of course it 
				//should be in the frame window ie hieght
				PlanetPositionY[SUNPlanetForLoop] = -PlanetRadius[SUNPlanetForLoop] - 50;
		}





		int BulletIndexForTheLoopUse = 0;
		while (BulletIndexForTheLoopUse < MAX_BULLETS) //maxbullets are 15;
		{
			if (!BulletActive[BulletIndexForTheLoopUse]) //bullet is inactive → use it
			{
				BulletActive[BulletIndexForTheLoopUse] = 1; //the bullet has now bacame active
				BulletPositionX[BulletIndexForTheLoopUse] = ShipW; //correct horizontal fire

				BulletPositionY[BulletIndexForTheLoopUse] = ShipHieght - 21; //vertical fire position
				WaitToFire = WaitToFireTime; //reset cooldown
				break;
			}

			BulletIndexForTheLoopUse++;
		}











		if (WaitToFire > 0)
		{
			WaitToFire--;

		}


		if (IsKeyDown(KEY_SPACE) && WaitToFire == 0)
		{


			//iskeyfunction; represesnts continuous action
			//key pressed + ready to fire(space ship)




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



		//now drawing bullets
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
	CloseWindow();
}

int main()
{
	DemonstrateGraphics();
		
	/*Color grey = {8, 4, 35, 255};
	//here we have created a color variable using the structure Color,this will showcase
	// grey color in the backgound.

	int WindowWidth = 1100;
	int WindowHieght = 900;
	//here we have declaraed the first two variables now these two are actually defining 
	// the total frame size which will be shown at the time of playing, widht will be declared more 
	//the height so by that it will be more presentable

	/*
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


	//here i have initialized planats lol'
	const int NumberOfPlanetsGoingToFall = 8;//the number of planets which are going to fall in the
	//window frame
	//now declaring the positions of the planets
	// i randomly tossed positions for the plaets 
	int PlanetPositionX[NumberOfPlanetsGoingToFall] = { 100, 400, 160, 206, 530, 605, 60, 76 };
	//horizontal
	int PlanetPositionY[NumberOfPlanetsGoingToFall] = { -100, -200, -150, -150, -250, -300, -100, 345};
	//vertical positions
	//now i am going for the radius of the planets 
	int PlanetRadius[NumberOfPlanetsGoingToFall] = { 30, 50, 38, 45, 35, 26, 14, 10 };//radius of the
	//8 planets some are very big, medium and very small
	//now i am going for speed of the planets iam have folowed the same pattern(random)
	//now for speed and colors;
	int PlanetFallingSpeed[NumberOfPlanetsGoingToFall] = { 2, 4, 1, 3, 2, 6, 5, 6 };
	//as it will have three layesr so: 
	Color PlanetFirstColor[NumberOfPlanetsGoingToFall] = { BLUE, RED, GOLD, GREEN, PURPLE, ORANGE, PINK, BROWN };
	Color PlanetSecondColors[NumberOfPlanetsGoingToFall] = { DARKBLUE, MAROON, ORANGE, DARKGREEN, MAGENTA, BROWN, GOLD, ORANGE };
	Color PlanetThirdColors[NumberOfPlanetsGoingToFall] = { BLUE, PINK, YELLOW, LIME, VIOLET, BEIGE, YELLOW, YELLOW };


	const int SUNPlanet = 1;
	//for sun in the center
	int SUNPlanetPositionX[SUNPlanet] = { 350 };
	int SUNPlanetPositionY[SUNPlanet] = { -500 };
	int SUNPlanetRadius[SUNPlanet] = { 60 };
	Color SUNPlanetFirstColor[SUNPlanet] = { YELLOW };
	Color SUNPlanetSecondColors[SUNPlanet] = { ORANGE };
	Color SUNPlanetThirdColors[SUNPlanet] = { GOLD };



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



		//here i am going to use a for loop to draw the planets and make them fall
		for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++)
		{//for the first layer:
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop], PlanetFirstColor[PlanetForLoop]);

			//for the second layer
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.7, PlanetSecondColors[PlanetForLoop]);

			//for the third loop
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.4, PlanetThirdColors[PlanetForLoop]);


			PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop]; //as if the planets move down
			//wrds they will cover more distance vertically from the top lol

			if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)//of course it 
				//should be in the frame window ie hieght
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


	while (WindowShouldClose() == false)
	{
		//again using function: will get detected if escape key is used or close icon
		//game will be closed if it turns true


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


// here i am going to repaste the code for planets i have made using a loop above: 
		//here i am going to use a for loop to draw the planets and make them fall
		for (int PlanetForLoop = 0; PlanetForLoop < NumberOfPlanetsGoingToFall; PlanetForLoop++)
		{//for the first layer:
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop], PlanetFirstColor[PlanetForLoop]);

			//for the second layer
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.7, PlanetSecondColors[PlanetForLoop]);

			//for the third loop
			DrawCircle(PlanetPositionX[PlanetForLoop], PlanetPositionY[PlanetForLoop], PlanetRadius[PlanetForLoop] * 0.4, PlanetThirdColors[PlanetForLoop]);


			PlanetPositionY[PlanetForLoop] += PlanetFallingSpeed[PlanetForLoop]; //as if the planets move down
			//wrds they will cover more distance vertically from the top lol

			if (PlanetPositionY[PlanetForLoop] - PlanetRadius[PlanetForLoop] > WindowHieght)//of course it 
				//should be in the frame window ie hieght
				PlanetPositionY[PlanetForLoop] = -PlanetRadius[PlanetForLoop] - 50;
		}


		for (int SUNPlanetForLoop = 0; SUNPlanetForLoop < NumberOfPlanetsGoingToFall; SUNPlanetForLoop++)
		{//for the first layer:
			DrawCircle(PlanetPositionX[SUNPlanetForLoop], PlanetPositionY[SUNPlanetForLoop], PlanetRadius[SUNPlanetForLoop], PlanetFirstColor[SUNPlanetForLoop]);
		//for the second layer
			DrawCircle(PlanetPositionX[SUNPlanetForLoop], PlanetPositionY[SUNPlanetForLoop], PlanetRadius[SUNPlanetForLoop] * 0.7, PlanetSecondColors[SUNPlanetForLoop]);
			//for the third loop
			DrawCircle(PlanetPositionX[SUNPlanetForLoop], PlanetPositionY[SUNPlanetForLoop], PlanetRadius[SUNPlanetForLoop] * 0.4, PlanetThirdColors[SUNPlanetForLoop]);
		

			PlanetPositionY[SUNPlanetForLoop] += PlanetFallingSpeed[SUNPlanetForLoop]; //as if the planets move down
			//wrds they will cover more distance vertically from the top lol

			if (PlanetPositionY[SUNPlanetForLoop] - PlanetRadius[SUNPlanetForLoop] > WindowHieght)//of course it 
				//should be in the frame window ie hieght
				PlanetPositionY[SUNPlanetForLoop] = -PlanetRadius[SUNPlanetForLoop] - 50;
		}





		int BulletIndexForTheLoopUse = 0;
		while (BulletIndexForTheLoopUse < MAX_BULLETS) //maxbullets are 15;
		{
			if (!BulletActive[BulletIndexForTheLoopUse]) //bullet is inactive → use it
			{
				BulletActive[BulletIndexForTheLoopUse] = 1; //the bullet has now bacame active
				BulletPositionX[BulletIndexForTheLoopUse] = ShipW; //correct horizontal fire

				BulletPositionY[BulletIndexForTheLoopUse] = ShipHieght - 21; //vertical fire position
				WaitToFire = WaitToFireTime; //reset cooldown
				break;
			}

			BulletIndexForTheLoopUse++;
		}











		if (WaitToFire > 0)
		{
			WaitToFire--;

		}


		if (IsKeyDown(KEY_SPACE) && WaitToFire == 0)
		{


			//iskeyfunction; represesnts continuous action
			//key pressed + ready to fire(space ship)




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



		//now drawing bullets
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
	}*/


	//the first thing we will do with the while loop is to check the events 
	//which are going to happen in the game 
	//CloseWindow();;

}





