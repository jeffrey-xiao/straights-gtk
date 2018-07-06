#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

enum class PlayerType { HUMAN, COMPUTER };

class Card;

class Player {
  private:
    std::vector<Card> cards_, discardedCards_;
    int score_;
    PlayerType type_;

  public:
    Player(PlayerType);

    std::vector<Card> getCards() const;
    void setCards(std::vector<Card>);
    void playCard(Card);
    void discardCard(Card);

    std::vector<Card> getDiscardedCards() const;

    PlayerType getPlayerType() const;
    void setPlayerType(PlayerType type);

    int getScore() const;
    int getRoundScore() const;

    void updateScore();
};

#endif
