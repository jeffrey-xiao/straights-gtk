#include "GameController.h"
#include "Player.h"
#include "TextUserInterface.h"

#include <iostream>
#include <vector>

int main(int argc, char** argv) {
  int seed = 0;
  if (argc == 2) {
    seed = atoi(argv[1]);
  }

  std::vector<PlayerType> playerTypes;
  playerTypes.reserve(4);
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::cout << "Is player " << i + 1 << " a human(h) or a computer(c)?" << std::endl;
    char c;
    std::cout << ">";
    std::cin >> c;

    if (c == 'h') {
      playerTypes.push_back(PlayerType::HUMAN);
    } else {
      playerTypes.push_back(PlayerType::COMPUTER);
    }
  }

  TextUserInterface *userInterface = new TextUserInterface();
  GameController *gameController = new GameController(seed, playerTypes, userInterface);
  userInterface->setGameController(gameController);

  userInterface->startGame();

  return 0;
}
