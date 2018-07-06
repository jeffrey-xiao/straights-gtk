#include "Command.h"
#include "Game.h"
#include "GameController.h"

#include <algorithm>
#include <cassert>

GameController::GameController(int seed, std::vector<PlayerType> playerTypes, Observer *userInterface):
  game_(new Game(seed, playerTypes, userInterface)) {}

GameController::~GameController() {
  delete game_;
}

void GameController::startGame() {
  game_->startRound();
}

void GameController::executeCommand(Command command) {
  switch (command.type) {
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

GameBoard GameController::getGameBoard() const {
  return game_->getGameBoard();
}

std::vector<Player> GameController::getPlayers() const {
  return game_->getPlayers();
}

std::vector<int> GameController::getWinners() const {
  // find the minimum score among all the players
  std::vector<Player> players = game_->getPlayers();
  int minScore = players[0].getScore();
  for (size_t i = 1; i < players.size(); i++) {
    minScore = std::min(minScore, players[i].getScore());
  }

  // find all players that have the minimum score
  std::vector<int> winners;
  for (size_t i = 0; i < players.size(); i++) {
    if (minScore == players[i].getScore()) {
      winners.push_back(i + 1);
    }
  }

  return winners;
}

int GameController::getCurrentPlayer() const {
  return game_->getCurrentPlayer() + 1;
}

Card GameController::getLastCard() const {
  return game_->getLastCard();
}

std::vector<Card> GameController::getCurrentPlayerCards() const {
  return game_->getCurrentPlayerCards();
}

std::vector<Card> GameController::getCurrentPlayerValidCards() const {
  return game_->getCurrentPlayerValidCards();
}

Deck GameController::getDeck() const {
  return game_->getDeck();
}

Game::GameState GameController::getGameState() const {
  return game_->getGameState();
}
