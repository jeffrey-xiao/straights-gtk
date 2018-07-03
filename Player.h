#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

enum PlayerType { HUMAN, COMPUTER };

class Card;

class Player {
  private:
    std::vector<Card> cards_, discardedCards_;
    int score_;
    PlayerType type_;

  public:
    std::vector<Card> getCards();
    void setCards(std::vector<Card>);
    void removeCard(Card);

    std::vector<Card> getDiscardedCards();

    PlayerType getPlayerType();

    int getScore();
    void setScore(int);
};

#endif
