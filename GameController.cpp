#include "Command.h"
#include "Game.h"
#include "GameController.h"

#include <algorithm>
#include <cassert>

GameController::GameController(int seed): game_(new Game(seed)) {}

GameController::~GameController() {
  delete game_;
}

void GameController::initGame() {
  game_->initGame();
}

void GameController::startGame(std::vector<PlayerType> playerTypes) {
  game_->startGame(playerTypes);
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

    case QUIT:
      game_->quit();
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

std::vector<Player> GameController::getWinners() const {
  // find the minimum score among all the players
  std::vector<Player> players = game_->getPlayers();
  int minScore = players[0].getScore();
  for (size_t i = 1; i < players.size(); i++) {
    minScore = std::min(minScore, players[i].getScore());
  }

  // find all players that have the minimum score
  std::vector<Player> winners;
  for (size_t i = 0; i < players.size(); i++) {
    if (minScore == players[i].getScore()) {
      winners.push_back(players[i]);
    }
  }

  return winners;
}

int GameController::getCurrentPlayerId() const {
  return game_->getCurrentPlayer().getId();
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

void GameController::addObserver(Observer *observer) {
  game_->addObserver(observer);
}

void GameController::setSeed(int seed) {
  game_->setSeed(seed);
}
