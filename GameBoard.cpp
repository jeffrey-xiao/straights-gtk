#include "Card.h"
#include "GameBoard.h"
#include "Straight.h"

#include <cassert>

const int STRAIGHT_COUNT = 4;

GameBoard::GameBoard() {
  straights_.reserve(STRAIGHT_COUNT);
  for (int i = 0; i < STRAIGHT_COUNT; i++) {
    straights_.push_back(Straight((Suit)i));
  }
}

void GameBoard::resetBoard() {
  for (int i = 0; i < SUIT_COUNT; i++) {
    straights_[i] = Straight((Suit)i);
  }
}

bool GameBoard::canPlayCard(Card card) const {
  Suit suit = card.getSuit();
  return straights_[suit].canPlayCard(card);
}

void GameBoard::playCard(Card card) {
  assert(canPlayCard(card));
  Suit suit = card.getSuit();
  straights_[suit].playCard(card);
}

std::ostream& operator<<(std::ostream &out, const GameBoard &gameBoard) {
  out << "Cards on the table:" << std::endl;
  for (Straight straight : gameBoard.straights_) {
    out << straight << std::endl;
  }
  return out;
}
