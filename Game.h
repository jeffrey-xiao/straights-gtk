#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Player.h"
#include "Straight.h"

#include <vector>

struct Command;
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

    int seed_;
    std::vector<Straight> straights_;
    std::vector<Player> players_;
    int currentPlayer_;
    std::vector<Card> deck_;
    Observer *userInterface_;
    GameState gameState_;
    Card lastCard_;

    Game(int, std::vector<PlayerType>, Observer*);

    std::vector<Card> getCurrentPlayerCards() const;
    std::vector<Card> getCurrentPlayerValidCards() const;

    void notify();
    void setGameState(GameState);
    void startRound();
    void runRound();
    void playCard(Card);
    void discardCard(Card);
    void ragequit();
};

#endif
