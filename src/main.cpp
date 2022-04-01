#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t kScreenWidth{640};
constexpr std::size_t kScreenHeight{640};
constexpr std::size_t kGridWidth{32};
constexpr std::size_t kGridHeight{32};

Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
Controller controller;


int main() {

  // Intiializes game and loads it
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);


  // Structs and logic added for displaying message box once the game ends
  const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "Yes" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No" },

    };
  const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
  const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "GAME END", /* .title */
        "Do you want to play again?", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
  };
  int buttonid;
  if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
  }
  if (buttonid == -1) {
        SDL_Log("No selection");
  } else if (buttonid == 0)  {

    // Recursively calling main to allow restarting any number of times
      main();

  }
  else{
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
  }

  return 0;
}