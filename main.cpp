#include "GameController.h"
#include "Player.h"
#include "GraphicalUserInterface.h"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
  int seed = 0;
  if (argc == 2) {
    seed = atoi(argv[1]);
  }

  std::vector<PlayerType> playerTypes;
  playerTypes.resize(4);
  for (size_t i = 0; i < playerTypes.size(); i++) {
    std::cout << "Is player " << i + 1 << " a human(h) or a computer(c)?" << std::endl;
    char c;
    std::cout << ">";
    std::cin >> c;

    if (c == 'h') {
      playerTypes[i] = PlayerType::HUMAN;
    } else {
      playerTypes[i] = PlayerType::COMPUTER;
    }
  }

  GraphicalUserInterface *userInterface = new GraphicalUserInterface();
  GameController *gameController = new GameController(seed, playerTypes, userInterface);
  userInterface->setGameController(gameController);
  userInterface->startGame();

  delete userInterface;
  delete gameController;

  return 0;
}
