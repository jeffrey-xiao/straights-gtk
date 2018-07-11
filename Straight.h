#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "Card.h"

class Straight {
  // Represents one "Straight" of cards in the game Straights
  // Specification Fields:
  //   suit = the suit of the straight
  //   cards = set of cards contained in the straight
  private:
    Suit suit_;
    Rank loRank_, hiRank_;

  public:
    explicit Straight(Suit);
    // ensures: initializes this to an empty straight with the specified suit,

    bool canPlayCard(Card card) const;
    // returns: true if the Card is a valid play on the straight
    //          false if the Card is not a valid play on the straight

    void playCard(Card card);
    // requires: canPlayCard(Card) is true
    // ensures: cards = cards@pre + card

    friend std::ostream& operator<<(std::ostream &out, const Straight &straight);
    // modifies: out
    // ensures: out = out@pre + straight.cards (in ascending order of rank)
    // returns: out
};

#endif
