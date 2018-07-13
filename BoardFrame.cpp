#include "BoardFrame.h"
#include "Card.h"
#include "Game.h"
#include "GameController.h"

BoardFrame::BoardFrame(GameController *gameController): Gtk::Frame("Cards on the table"),
  gameController_(gameController)
{
  set_border_width(6);
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
  if (gameState == Game::GameState::HUMAN_INPUT || gameState == Game::GameState::ROUND_END) {
    GameBoard gameBoard = gameController_->getGameBoard();
    for (size_t i = 0; i < SUIT_COUNT; i++) {
      for (size_t j = 0; j < RANK_COUNT; j++) {
        size_t index = i * RANK_COUNT + j;
        Card currCard((Suit)i, (Rank)j);
        if (gameBoard.hasCard(currCard)) {
          cardImages_[index].set(CARD_IMG_PREFIX + currCard.getString() + CARD_IMG_SUFFIX);
        } else {
          cardImages_[index].set(NOTHING_IMG);
        }
      }
    }
  } else if (gameState == Game::GameState::ROUND_START) {
    reset();
  }
}

void BoardFrame::reset() {
  for (size_t i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
    cardImages_[i].set("img/nothing.png");
  }
}
