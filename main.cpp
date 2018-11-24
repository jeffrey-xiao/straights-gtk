#include "GameController.h"
#include "Player.h"
#include "StraightsGui.h"

#include <vector>

int main(int argc, char **argv) {
  int seed = 0;
  if (argc == 2) {
    seed = atoi(argv[1]);
  }

  GameController *gameController = new GameController(seed);
  StraightsGui *userInterface = new StraightsGui(gameController);
  gameController->initGame();

  delete userInterface;
  delete gameController;

  return 0;
}
