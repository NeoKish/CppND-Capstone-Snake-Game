#include "food.h"
#include<iostream>


void Food::PlaceFood(int x, int y , Snake &snake) {

 
  while (true) {

    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y))  {

      food_item.x = x;
      food_item.y = y;
      return;
    }
  }
}

bool Food::CheckFood(Snake &snake){


    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    if(food_item.x == new_x && food_item.y == new_y)

        return true;
    else
        return false;
        
}