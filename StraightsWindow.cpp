#include "StraightsWindow.h"

StraightsWindow::StraightsWindow(GraphicalUserInterface *root): root_(root) {
  set_title("Straights");
  set_default_size(400, 400);

  add(contents_);
  contents_.pack_start(menuFrame_);
  contents_.pack_start(deckFrame_);

  contents_.pack_start(playerContents_);
  playerFrames_.reserve(4);
  for (size_t i = 0; i < 4; i++) {
    playerFrames_.push_back("Player " + std::to_string(i));
    playerContents_.pack_start(playerFrames_[i]);
  }

  contents_.pack_start(handFrame_);

  show_all_children();
}
