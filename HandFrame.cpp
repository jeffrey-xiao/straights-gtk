#include "Card.h"
#include "Command.h"
#include "GameController.h"
#include "HandFrame.h"

#include <gtkmm/button.h>

#include <algorithm>
#include <iostream>
#include <vector>

HandFrame::HandFrame(GameController *gameController): Gtk::Frame("Hand Frame"),
  gameController_(gameController), isDiscard_(false)
{
  gameController_->addObserver(this);
  hand_.reserve(RANK_COUNT);

  for (size_t i = 0; i < RANK_COUNT; i++) {
    hand_.push_back(CardButton(this));
  }

  add(contents_);
  for (Gtk::Button &c : hand_) {
    contents_.pack_start(c);
    c.set_sensitive(false);
  }
  contents_.set_spacing(10);
  show_all_children();
}

void HandFrame::update() {
  std::vector<Card> cards = gameController_->getCurrentPlayerCards();
  std::vector<Card> legalPlays = gameController_->getCurrentPlayerValidCards();

  isDiscard_ = legalPlays.empty();

  for (size_t i = 0; i < cards.size(); i++) {
    hand_[i].setCard(cards[i]);
    if (legalPlays.empty() || std::find(legalPlays.begin(), legalPlays.end(), cards[i]) != legalPlays.end()) {
      hand_[i].set_sensitive(true);
    } else {
      hand_[i].set_sensitive(false);
    }
  }

  for (size_t i = cards.size(); i < RANK_COUNT; i++) {
    hand_[i].reset();
    hand_[i].set_sensitive(false);
  }
}

void HandFrame::executeCommand(Card card) {
  Command command;
  command.card = card;
  if(isDiscard_) {
    command.type = DISCARD;
  } else {
    command.type = PLAY;
  }

  gameController_->executeCommand(command);
}

