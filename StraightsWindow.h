#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H

#include <gtkmm.h>
#include "DeckFrame.h"
#include "MenuFrame.h"

class StraightsWindow : public Gtk::ApplicationWindow {
  public:
    StraightsWindow();

  private:
    Gtk::VBox contents_;
    DeckFrame deckFrame_;
    MenuFrame menuFrame_;
};

#endif
