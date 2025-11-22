# Raylib project
My First Group Project on the Construction of a Game
Programming Fundamentals Group Project
Space shooter:
First step:
The first step was to set up a blank screen of course constituting a background and creating a loop, I used Raylib as a library in the project.
Game loop covers the repetition of the game objects and collisions. Now we need to specify the game window where our objects will be shown 
Now we are going to use coordinates for the game where the coordinates in a computer system starts from the top left corner of the window. Here the x coordinate will increase by moving right and y coordinate will get increased by moving downwards from the origin. Moving towards the game loop, it is divided into three parts in the first we need to set up the loop covering any event which is happening including input from keys pressed on the keyboard and quitting the game 
Second part will be covering any changes or updating in the positions of objects like from where they were to where they are going to be now. The last part will be regarding the drawing of objects or their demonstration. We are going to use a while loop which is going to run over and over again until the game will get ended. In raylib there is a function colour = {red, green, blue, alpha}
And have 0 to 255 with the colour will show its maximum intensity at 255
For red colour the code will be : colour red = {255, 0, 0, 255}
Showcasing the values for: colour = {red, green, blue, alpha}
For defining the space ship:
First I used 4 variables including first two as creating a position for the space ship and other two being as initialized moreover, I studied that raylib makes a rectangle for example from the left not the center so because of that I had to subtract half of the window width from it, 
For the space ship after defining the four variables I then used calculations to ensure the figure or the demonstration of the space ship, however I used these shapes including : a rectangle for the body then a circle for the cockpit show casing the center body of it and for wings, for left and for right I used the same measurements with a circle and for exhaust or the fumes from the burning of engine I used the circle again.
When I subtracted a larger number from the width and height the ship resulted was distorted. For the wings the much I subtracted the more the wings get  further.
Now I am going for the creation of the ship of enemies:
What I am going to do is just to first declare some variables as I did for the ship of the player and after creating visuals for these I will work on the movements
I again declared first the enemies ship Enemy ship width will be window width / 2 so that it will appear exactly from the centre of the screen now for the height it is going to be almost a minimal measurement as at 0 it will be at the most top position but I want the space ship to be at a little lower position so for that I am taking the height measurement about 45.
As the space ship of the enemies is also going downwards so I took a variable as for the speed of the spacecraft and was set at 2 as at this it will not be too fast and not be too slow as at 1 it will be very slow.
Now I am going to work on the movements so first of all, I am going to use a raylib function which is: IsKeyDown which I am going for : (KEY_RIGHT) and (KEY_LEFT), now this function will check two conditions if the player have pressed right arrow key then true value will be given and the spaceship will move right, and if left arrow key is pressed same function will get repeated. If none or other keys are pressed then false value will get returned. The spaceship will not move
So now I am going for the enemies how they are going to get spawned and how they will move forward towards the ship of the player.
I declared different variables for the enemies including the horizontal and vertical points here I am going to use an array in which for the variables they are horizontal and vertical positions of the enemies along with their speed moreover I have used a loop along with it too in this I have declared that with the increase in value of I, a random number will get generated along with a range. Now at two points I have used a variable regarding the speed of the enemy ship. So here one is defining the continuous position change and the other is defining actual speed.
Now I am moving on to the bullets so first of all I am declaring how maximum number of bullets can be fired within the window frame at once. Now I am initializing 2 variables concerning with the position of the variables vertically and horizontally. Also I have mentioned a variable restating 





