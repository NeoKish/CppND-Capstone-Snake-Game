#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include "snake.h"


enum Type { Right, Wrong};

class Food
{
    public:
    
        Food(Type type_id):_type_id(type_id) {};
        void PlaceFood(int x, int y ,Snake &snake);
        bool CheckFood(Snake &snake);
        SDL_Point food_item;
    
    private:

        Type _type_id;

};

#endif