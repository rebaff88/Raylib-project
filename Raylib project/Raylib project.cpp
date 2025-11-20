#include<raylib.h>  //library we are going to use

int main()
{
	Color grey = { 22, 27, 27, 255 };
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

	while (WindowShouldClose() == false)
		//again using function: will get detected if escape key is used or close icon
		//game will be closed if it turns true
	{
		BeginDrawing(); //will create a black screen

		ClearBackground(grey);//after clearing bg will be grey

		EndDrawing();   //will end the black screen
	}
	//the first thing we will do with the while loop is to check the events 
	//which are going to happen in the game 
	CloseWindow();

}

