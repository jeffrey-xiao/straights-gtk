#include "StraightsWindow.h"

StraightsWindow::StraightsWindow() : Gtk::ApplicationWindow(), deckFrame_() {
  set_title("Straights");
  add(deckFrame_);
  show_all_children();
}
