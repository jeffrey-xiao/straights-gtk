#include "Card.h"
#include "Player.h"

#include <algorithm>
#include <cassert>

Player::Player(PlayerType type): type_(type) {}

std::vector<Card> Player::getCards() const {
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

std::vector<Card> Player::getDiscardedCards() const {
  return discardedCards_;
}

PlayerType Player::getPlayerType() const {
  return type_;
}

void Player::setPlayerType(PlayerType type) {
  type_ = type;
}

int Player::getScore() const {
  return score_;
}

void Player::setScore(int score) {
  score_ = score;
}
