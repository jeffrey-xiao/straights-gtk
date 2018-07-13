#include "Card.h"
#include "Straight.h"

#include <cassert>

// initialize loRank_ to EIGHT and hiRank_ to SIX to account for the corner cases where no cards
// have been played for a particular straight.
Straight::Straight(Suit suit): suit_(suit), loRank_(EIGHT), hiRank_(SIX) {};

bool Straight::canPlayCard(Card card) const {
  Suit suit = card.getSuit();
  if (suit_ != suit) {
    return false;
  }

  Rank rank = card.getRank();

  if (hiRank_ == rank - 1) {
    return true;
  }

  if (loRank_ == rank + 1) {
    return true;
  }

  return false;
}

void Straight::playCard(Card card) {
  assert(canPlayCard(card));
  Rank rank = card.getRank();

  if (hiRank_ == rank - 1) {
    hiRank_ = rank;
  }

  if (loRank_ == rank + 1) {
    loRank_ = rank;
  }
}

bool Straight::canUndoMove(Card card) const {
  Suit suit = card.getSuit();
  if (suit_ != suit) {
    return false;
  }

  Rank rank = card.getRank();

  if (hiRank_ == rank || loRank_ == rank) {
    return true;
  }

  return false;
}

void Straight::undoMove(Card card) {
  assert(canUndoMove(card));

  Rank rank = card.getRank();

  if (hiRank_ == rank) {
    hiRank_ = (Rank) (hiRank_ - 1);
  }

  if (loRank_ == rank) {
    loRank_ = (Rank) (loRank_ + 1);
  }
}

bool Straight::hasCard(Card card) const {
  if (card.getSuit() != suit_) {
    return false;
  }
  return loRank_ <= card.getRank() && card.getRank() <= hiRank_;
}

std::ostream& operator<<(std::ostream &out, const Straight &straight) {
  std::string suits[SUIT_COUNT] = {"Clubs", "Diamonds", "Hearts", "Spades"};
  std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "J", "Q", "K"};

  out << suits[straight.suit_] << ":";
  if (straight.loRank_ <= straight.hiRank_) {
    out << " ";
  }

  for (int i = straight.loRank_; i <= straight.hiRank_; i++) {
    out << ranks[i];
    if (i != straight.hiRank_) {
      out << " ";
    }
  }

  return out;
}
