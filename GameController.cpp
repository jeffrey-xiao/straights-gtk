#include "Command.h"
#include "Game.h"
#include "GameController.h"

#include <algorithm>
#include <cassert>

GameController::GameController(int seed, std::vector<PlayerType> playerTypes, Observer *userInterface):
  game_(new Game(seed, playerTypes, userInterface)), nextCommand_(Command()) {}

GameController::~GameController() {
  delete game_;
}

void GameController::startGame() {
  game_->startRound();

  do {
    executeNextCommand();
  } while (nextCommand_.type != BAD_COMMAND); 

}

void GameController::setNextCommand(Command command) {
  nextCommand_ = command;
}
void GameController::executeNextCommand() {
  Command command = nextCommand_;
  nextCommand_ = Command();

  switch (nextCommand_.type) {
    case PLAY:
      game_->playCard(command.card);
      break;

    case DISCARD:
      game_->discardCard(command.card);
      break;

    case RAGEQUIT:
      game_->ragequit();
      break;

    default:
      assert(false);
  }
}

std::vector<Straight> GameController::getStraights() const {
  return game_->straights_;
}

std::vector<Player> GameController::getPlayers() const {
  return game_->players_;
}

std::vector<int> GameController::getWinners() const {
  int minScore = game_->players_[0].getScore();
  for (int i = 1; i < PLAYER_COUNT; i++) {
    minScore = std::min(minScore, game_->players_[i].getScore());
  }

  std::vector<int> winners;
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (minScore == game_->players_[i].getScore()) {
      winners.push_back(i + 1);
    }
  }

  return winners;
}

int GameController::getCurrentPlayer() const {
  return game_->currentPlayer_ + 1;
}

Card GameController::getLastCard() const {
  return game_->lastCard_;
}

std::vector<Card> GameController::getCurrentPlayerCards() const {
  return game_->getCurrentPlayerCards();
}

std::vector<Card> GameController::getCurrentPlayerValidCards() const {
  return game_->getCurrentPlayerValidCards();
}

std::vector<Card> GameController::getDeck() const {
  return game_->deck_;
}

Game::GameState GameController::getGameState() const {
  return game_->gameState_;
}
