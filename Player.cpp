#include "Card.h"
#include "Player.h"

#include <algorithm>
#include <cassert>

std::vector<Card> Player::getCards() {
  return cards_;
}

void Player::setCards(std::vector<Card> cards) {
  cards_ = cards;
}

void Player::removeCard(Card card) {
  auto iter = std::find(cards_.begin(), cards_.end(), card);
  assert(iter != cards_.end());
  discardedCards_.push_back(*iter);
  cards_.erase(iter);
}

std::vector<Card> Player::getDiscardedCards() {
  return discardedCards_;
}

PlayerType Player::getPlayerType() {
  return type_;
}

int Player::getScore() {
  return score_;
}

void Player::setScore(int score) {
  score_ = score;
}
