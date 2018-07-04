#include "Card.h"
#include "Straight.h"

Straight::Straight(Suit suit): suit_(suit), loRank_((Rank)8), hiRank_((Rank)6) {};

Rank Straight::getLoRank() const {
  return loRank_;
}

Rank Straight::getHiRank() const {
  return hiRank_;
}

void Straight::setLoRank(Rank loRank) {
  loRank_ = loRank;
}

void Straight::setHiRank(Rank hiRank) {
  hiRank_ = hiRank;
}

// TODO: Should the view be responsible for this representation or is it generic enough to be a 
// << operator?
std::ostream& operator<<(std::ostream &out, const Straight &straight) {
  std::string suits[SUIT_COUNT] = {"Clubs", "Diamonds", "Hearts", "Spades"};
  std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"};

  out << suits[straight.suit_] << ": ";
  for (int i = straight.loRank_; i <= straight.hiRank_; i++) {
    out << ranks[i] << " ";
  }

  return out;
}
