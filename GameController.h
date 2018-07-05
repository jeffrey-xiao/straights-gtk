#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Game.h"
#include "Command.h"

#include <vector>

class Card;
class Observer;
class Straight;
class Player;
enum class PlayerType;

class GameController {
  private:
    Game *game_;
    Command nextCommand_;
    void executeNextCommand();

  public:
    GameController(int, std::vector<PlayerType>, Observer *);
    ~GameController();

    void startGame();
    void setNextCommand(Command);

    std::vector<Straight> getStraights() const;
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
