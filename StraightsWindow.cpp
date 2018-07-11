#include "GameController.h"
#include "StraightsWindow.h"

StraightsWindow::StraightsWindow(GameController *gameController): gameController_(gameController),
  boardFrame_(gameController), menuFrame_(gameController), handFrame_(gameController)
{
  set_title("Straights");
  set_default_size(400, 400);

  add(contents_);
  contents_.pack_start(menuFrame_);
  contents_.pack_start(boardFrame_);

  contents_.pack_start(playerContents_);
  playerFrames_.reserve(4);
  for (size_t i = 0; i < 4; i++) {
    playerFrames_.push_back(new PlayerFrame(gameController, "Player " + std::to_string(i + 1)));
    playerContents_.pack_start(*playerFrames_[i]);
  }

  contents_.pack_start(handFrame_);

  show_all_children();
}

StraightsWindow::~StraightsWindow() {
  for (PlayerFrame *playerFrame : playerFrames_) {
    delete playerFrame;
  }
}

void StraightsWindow::update() {

}
