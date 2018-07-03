#ifndef STRAIGHT_H
#define STRAIGHT_H

#include "Card.h"

class Straight {
  private:
    Suit suit_;
    Rank loRank_, hiRank_;

  public:
    Straight(Suit);

    Rank getLoRank();
    Rank getHiRank();

    void setLoRank(Rank);
    void setHiRank(Rank);

    friend std::ostream& operator<<(std::ostream &, const Straight &);
};

#endif
