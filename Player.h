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
  explicit Player(int id);
  // ensures: initializes this to a Player with the specified id
  //          with score = 0, hand = empty, discarded = empty, type = COMPUTER

  std::vector<Card> getCards() const;
  // returns: cards

  void setCards(const std::vector<Card> &cards);
  // modifies: this
  // requires: cards.size() <= 13
  // ensures: hand = cards

  void playCard(Card card);
  // modifies: this
  // requires: card is in hand
  // ensures: hand = hand@pre - card

  void discardCard(Card);
  // modifies: this
  // requires: card is in hand
  // ensures: hand = hand@pre - card, discarded = discarded@pre + card

  std::vector<Card> getDiscardedCards() const;
  // returns: discarded

  PlayerType getPlayerType() const;
  // returns: type

  int getId() const;
  // returns: id

  void setPlayerType(PlayerType type);
  // modifies: this
  // ensures: type is set to the specified type

  int getScore() const;
  // returns: score

  int getRoundScore() const;
  // returns: sum of the scores of the discarded cards

  void updateScore();
  // modifies: this
  // ensures: score = score + roundScore, discarded = empty

  void reset();
  // modifies: this
  // ensures: score = 0, discarded = empty

  void undoMove(Card);
  // modifies: this
  // ensures: adds card to hand and removes the specified Card from discard pile (if is there)
};

#endif
