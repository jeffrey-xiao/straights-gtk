#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>

class Deck {
  // Represents a deck of 52 unique poker cards
  // Specification Fields:
  //   cards = the list of poker cards
  public:
    Deck();
    // ensures: initializes this to Deck with cards with initial order
    //          AC 2C 3C ... QC KC AD 2D ... QD KD AH 2H ... QH KH AS 2S ... QS KS

    std::vector<Card> getCards() const;
    // returns: cards

    std::vector<Card> getHand(int i) const;
    // requires: 0 <= i < 4
    // returns: list of 13 cards storing the i'th player's hand

    void shuffle(int seed);
    // ensures: the order of cards is shuffled

    Card& operator[](const int index);
    // returns: the card at position index in cards

  private:
    std::vector<Card> cards_;
};

#endif
