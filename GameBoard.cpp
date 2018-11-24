#include "GameBoard.h"
#include "Card.h"
#include "Straight.h"

#include <cassert>

GameBoard::GameBoard() {
  straights_.reserve(SUIT_COUNT);
  for (int i = 0; i < SUIT_COUNT; i++) {
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

void GameBoard::undoMove(Card card) {
  Suit suit = card.getSuit();
  if (straights_[suit].canUndoMove(card)) {
    straights_[suit].undoMove(card);
  }
}

bool GameBoard::hasCard(Card card) const {
  for (size_t i = 0; i < SUIT_COUNT; i++) {
    if (straights_[i].hasCard(card)) {
      return true;
    }
  }
  return false;
}

std::ostream &operator<<(std::ostream &out, const GameBoard &gameBoard) {
  out << "Cards on the table:" << std::endl;
  for (Straight straight : gameBoard.straights_) {
    out << straight << std::endl;
  }
  return out;
}
