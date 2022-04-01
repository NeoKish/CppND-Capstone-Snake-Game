# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## Changes made to the game

1. The games has been modified to include wrong foods(red ones) which when eaten by snake reduces snake's body size and speed. User has been given three life chances to continue playing the game if the snake dies in case of snake head hitting its own body or snake eating wrong food when its body size is one. 

2. The title window shows the value of lives remaining and updates as the lives get reduced. Everytime a life chance is lost, the window refreshes with new positions of foods. 

3. At the end of the game when all lives are lost, a dialog msg appears which allows you to restart the game if you want to continue the game. 

## Rubric points addressed

1. The project demonstrates an understanding of C++ functions and control structures.

In snake.cpp, the exisiting code for growth of snake body has been modified to include logic for reducing snake's body. For this purpose, switch statement where based on the value of the enum class growing, decision has been made to grow, reduce or not change. The following code is visible in UpdateBody() function from line 58 onwards. 

For adding new feature of live counter for snake, new logic have been added on two instances of snake dying. One is when snake eats wrong food when its size is one and the other is when snake head hits its own body. 
The logic for the first instance is added in game.cpp from line 91 onwards in the Update() function and second instance logic is added from line 74 onwards inside UpdateBody(). When snake hit itself, the snake body and size is reset to default irrespective of how much it has grown before hitting itself.

2. The project uses Object Oriented Programming techniques.

New translations units food.h and food.cpp are created. 
Food constructor is defined with Type of food as argument. A Type named enum has been created to initialise with right or wrong food. 

3. Classes use appropriate access specifiers for class members.
Food class consist of public member functions and variables as well as a private member. 
New member functions and member variables are added in snake.h and game.h for checking the lives count and refreshing the placement of food when the snake dies.

4. Class constructors utilize member initialization lists.
Food constructor does use of member initialization list.

5. Classes abstract implementation details from their interfaces.
The member functions PlaceFood and CheckFood have appropriate functions names. One is void and other is a boolean function which is explanantory with the function name given.

6. The project makes use of references in function declarations.
The member functions PlaceFood and CheckFood have Snake object being passed as reference.

main.cpp was modified to add the message box when the game run ends after user has lost all life chances and calls main function recursively so that the restart can happen more than once.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
