#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

enum class PlayerType { HUMAN, COMPUTER };

class Card;

class Player {
  // Represents a player in a game of Straights
  // Specification Fields:
  //   id = the players id in the game
  //   score = the players score in the game
  //   hand = the cards in the players hand, hand size is less than or equal to 13
  //   discarded = the cards the player has discarded in the round
  //   type = the type of player (Computer, Human)

  private:
    int id_;
    std::vector<Card> cards_, discardedCards_;
    int score_;
    PlayerType type_;

  public:
    Player(int i, PlayerType type);
    // ensures: initializes this to a Player with the specified id and type
    //          with score = 0, hand = empty, discarded = empty

    std::vector<Card> getCards() const;
    // returns: cards

    void setCards(std::vector<Card> cards);
    // requires: cards.size() <= 13
    // ensures: hand = cards

    void playCard(Card card);
    // requires: card is in hand
    // ensures: hand = hand@pre - card

    void discardCard(Card);
    // requires: card is in hand
    // ensures: hand = hand@pre - card, discarded = discarded@pre + card

    std::vector<Card> getDiscardedCards() const;
    // returns: discarded

    PlayerType getPlayerType() const;
    // returns: type

    int getId() const;
    // returns: id

    void setPlayerType(PlayerType type);
    // ensures: type is set to the specified type

    int getScore() const;
    // returns: score

    int getRoundScore() const;
    // returns: sum of the scores of the discarded cards

    void updateScore();
    // ensures: score = score + roundScore, discarded = empty
};

#endif
