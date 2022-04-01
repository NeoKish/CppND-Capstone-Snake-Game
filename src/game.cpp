#include "game.h"
#include <iostream>
#include "SDL.h" 
#include <thread>
#include <future>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      right_food(Type::Right),
      // wrong_food(Type::Wrong),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
 
    right_food.PlaceFood(random_w(engine),random_h(engine),snake);


    // Initialising wrong foods vector
    int i = 0;
    while(i<3){

      Food wrong_food(Type::Wrong);

      wrong_food.PlaceFood(random_w(engine),random_h(engine),snake);

      wrong_foods.push_back(wrong_food) ;
    
      ++i;
    }

}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;
  
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
  
    if(refresh){

      // Added a delay for smoother refreshing of placement of foods when snake dies
      SDL_Delay(200);
      RefreshFoods();
      
    }

    // renderer.Render(snake, right_food.food_item, wrong_food.food_item);
    renderer.Render(snake, right_food.food_item, wrong_foods);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, snake.count_lives);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  // Delay added for smooth transition to message box
  SDL_Delay(500);

}


void Game::Update() {

  snake.Update();

  if(snake.refresh && snake.count_lives!=0){
    refresh =true;
    snake.refresh =false;
  }
  else if (snake.count_lives==0) 
  {
      snake.alive = false;
      running=false;
  }

  // Check if there's food over here
  if (right_food.CheckFood(snake)) {

    score++;
    right_food.PlaceFood(random_w(engine),random_h(engine),snake);
    // Grow snake body and increase speed.
    
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Added logic for checking wrong food 
  for(auto &wrong_food: wrong_foods){

    if (wrong_food.CheckFood(snake) && snake.size>1) {
    
      score--;
      wrong_food.PlaceFood(random_w(engine),random_h(engine),snake);

      // Reduce snake body and decrease speed.
      snake.ReduceBody();
      snake.speed -= 0.02;

    }
    // Following logic checks wrong food and keep track of the how many lives are remaining for snake
    else if(wrong_food.CheckFood(snake) && snake.count_lives!=0) {


        // snake.head_x = random_w(engine);
        // snake.head_y = random_h(engine);
        --snake.count_lives;
        refresh = true;
        

    }

  }
  
}

void Game::RefreshFoods(){

    right_food.PlaceFood(random_w(engine),random_h(engine),snake);

    for(auto &wrong_food:wrong_foods)
      wrong_food.PlaceFood(random_w(engine),random_h(engine),snake);

    refresh = false;  

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }