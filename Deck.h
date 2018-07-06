#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>

class Deck {
  public:
    Deck();
    std::vector<Card> getHand(int) const;
    void shuffle(int);
    Card& operator[](const int index);
  private:
    std::vector<Card> cards_;
};

#endif
