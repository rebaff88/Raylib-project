#include<raylib.h>  //library we are going to use

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


	while (WindowShouldClose() == false)
		//again using function: will get detected if escape key is used or close icon
		//game will be closed if it turns true
	{
		BeginDrawing(); //will create a black screen

		ClearBackground(grey);//after clearing bg will be grey

		// Now loop first part; space ship craetion
		DrawRectangle(ShipW - 15, ShipH - 10, 30, 20, BLUE);//main body
		DrawCircle(ShipW, ShipH - 5, 7, BLUE);//center or cockpit,with 7 asradius,others-positon
		DrawCircle(ShipW - 20, ShipH + 5, 6, DARKBLUE);//wing 1(left)
		DrawCircle(ShipW + 20, ShipH + 5, 6, DARKBLUE);//wing2(right;-ve coordinate)
		DrawCircle(ShipW - 7, ShipH + 12, 5, ORANGE);//engine fume;left
		DrawCircle(ShipW + 7, ShipH + 12, 5, ORANGE);//engine fume; right



		EndDrawing();   //will end the black screen
	}
	//the first thing we will do with the while loop is to check the events 
	//which are going to happen in the game 
	CloseWindow();

}

