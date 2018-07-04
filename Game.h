#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Card.h"

struct Command;
class Player;
enum class PlayerType;
class Straight;
class Observer;

const int CARD_COUNT = 52;
const int STRAIGHT_COUNT = 4;
const int PLAYER_COUNT = 4;
const int MAX_SCORE = 80;

class Game {
  public:
    enum class GameState {
      ROUND_START,
      HUMAN_INPUT,
      INVALID_PLAY_INPUT,
      INVALID_DISCARD_INPUT,
      DISCARDED_CARD,
      PLAYED_CARD,
      ROUND_END,
      GAME_END,
    };

  private:
    int seed_;
    std::vector<Straight> straights_;
    std::vector<Player> players_;
    int currentPlayer_;
    std::vector<Card> deck_;
    Observer *userInterface_;
    GameState gameState_;
    Card lastCard_;

    void notify();
    void runRound();

  public:
    Game(int, std::vector<PlayerType>, Observer*);
    std::vector<Straight> getStraights() const;
    std::vector<Player> getPlayers() const;
    std::vector<int> getWinners() const;
    int getCurrentPlayer() const;
    Card getLastCard() const;
    std::vector<Card> getCurrentPlayerCards() const;
    std::vector<Card> getCurrentPlayerValidCards() const;
    std::vector<Card> getDeck() const;
    GameState getGameState() const;
    void startRound();
    void executeCommand(Command);
};

#endif
