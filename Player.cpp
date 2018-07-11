#include "Card.h"
#include "Player.h"

#include <algorithm>
#include <cassert>

Player::Player(int id): id_(id), cards_(), discardedCards_(), score_(0), type_(PlayerType::COMPUTER) {}

std::vector<Card> Player::getCards() const {
  return cards_;
}

void Player::setCards(std::vector<Card> cards) {
  cards_ = cards;
}

void Player::playCard(Card card) {
  // remove the card from hand
  auto iter = std::find(cards_.begin(), cards_.end(), card);
  assert(iter != cards_.end());
  cards_.erase(iter);
}

void Player::discardCard(Card card) {
  // remove the card from hand
  auto iter = std::find(cards_.begin(), cards_.end(), card);
  assert(iter != cards_.end());

  // add card to discard pile
  discardedCards_.push_back(*iter);
  cards_.erase(iter);
}

std::vector<Card> Player::getDiscardedCards() const {
  return discardedCards_;
}

PlayerType Player::getPlayerType() const {
  return type_;
}

int Player::getId() const {
  return id_;
}
void Player::setPlayerType(PlayerType type) {
  type_ = type;
}

int Player::getScore() const {
  return score_;
}

int Player::getRoundScore() const {
  int roundScore = 0;
  for (size_t i = 0; i < discardedCards_.size(); i++) {
    roundScore += discardedCards_[i].getRank() + 1;
  }
  return roundScore;
}

void Player::updateScore() {
  score_ += getRoundScore();
  discardedCards_.clear();
}

void Player::reset() {
  score_ = 0;
  discardedCards_.clear();
}
