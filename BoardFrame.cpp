#include "BoardFrame.h"
#include "Card.h"
#include "Game.h"
#include "GameController.h"

BoardFrame::BoardFrame(GameController *gameController): Gtk::Frame("Cards on the table"),
  gameController_(gameController)
{
  gameController_->addObserver(this);
  add(contents_);

  contents_.set_spacing(5);
  for (size_t i = 0; i < SUIT_COUNT; i++) {
    contents_.pack_start(straightBoxes_[i]);
    straightBoxes_[i].set_spacing(10);
  }

  reset();

  for (size_t i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
    straightBoxes_[i / RANK_COUNT].pack_start(cardImages_[i]);
  }

  show_all_children();
}

void BoardFrame::update() {
  Game::GameState gameState = gameController_->getGameState();
  if (gameState == Game::GameState::PLAYED_CARD) {
    Card card = gameController_->getLastCard();
    cardImages_[card.getSuit() * RANK_COUNT + card.getRank()].set("img/" + card.getString() + ".png");
  } else if (gameState == Game::GameState::ROUND_START) {
    reset();
  }
}

void BoardFrame::reset() {
  for (size_t i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
    cardImages_[i].set("img/nothing.png");
  }
}
