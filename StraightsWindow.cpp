#include "StraightsWindow.h"

StraightsWindow::StraightsWindow() {
  set_title("Straights");
  set_default_size(400, 400);
  add(contents_);
  contents_.pack_start(menuFrame_);
  contents_.pack_start(deckFrame_);
  show_all_children();
}
