#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>

class Deck {
  public:
    Deck();
    std::vector<Card> getCards() const;
    std::vector<Card> getHand(int) const;
    void shuffle(int);
  private:
    std::vector<Card> cards_;
};

#endif
