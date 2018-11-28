#include "GameController.h"
#include "Player.h"
#ifdef DEBUG
#include "StraightsTui.h"
#else
#include "StraightsGui.h"
#endif

#include <vector>

int main(int argc, char **argv) {
  int seed = 0;
  if (argc == 2) {
    seed = atoi(argv[1]);
  }

  GameController *gameController = new GameController(seed);
#ifdef DEBUG
  StraightsTui *userInterface = new StraightsTui(gameController);
#else
  StraightsGui *userInterface = new StraightsGui(gameController);
#endif
  gameController->initGame();

  delete userInterface;
  delete gameController;

  return 0;
}
