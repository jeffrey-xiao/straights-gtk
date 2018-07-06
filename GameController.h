#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Game.h"

#include <vector>

class Card;
struct Command;
class Observer;
class Player;
enum class PlayerType;

class GameController {
  private:
    Game *game_;

  public:
    GameController(int, std::vector<PlayerType>, Observer *);
    ~GameController();

    void startGame();
    void executeCommand(Command);

    GameBoard getGameBoard() const;
    std::vector<Player> getPlayers() const;
    std::vector<int> getWinners() const;
    int getCurrentPlayer() const;
    Card getLastCard() const;
    std::vector<Card> getCurrentPlayerCards() const;
    std::vector<Card> getCurrentPlayerValidCards() const;
    std::vector<Card> getDeck() const;
    Game::GameState getGameState() const;
};

#endif
