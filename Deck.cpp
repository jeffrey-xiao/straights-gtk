#include "Deck.h"
#include "Card.h"

#include <random>
#include <vector>

Deck::Deck() {
  cards_.reserve(SUIT_COUNT * RANK_COUNT);
  for (int i = 0; i < SUIT_COUNT; i++) {
    for (int j = 0; j < RANK_COUNT; j++) {
      cards_.push_back(Card((Suit)i, (Rank)j));
    }
  }
}

std::vector<Card> Deck::getHand(int i) const {
  auto first = cards_.begin() + 13 * i;
  auto last = cards_.begin() + 13 * (i + 1);
  std::vector<Card> hand(first, last);
  return hand;
}

void Deck::shuffle(int seed) {
  static std::mt19937 rng(seed);
  int n = SUIT_COUNT * RANK_COUNT;
  while (n > 1) {
    int k = (int)(rng() % n--);
    std::swap(cards_[k], cards_[n]);
  }
}

Card &Deck::operator[](const int index) {
  return cards_[index];
}
