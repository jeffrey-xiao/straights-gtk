#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H

#include <gtkmm.h>
#include "DeckFrame.h"

class StraightsWindow : public Gtk::ApplicationWindow {
  public:
    StraightsWindow();

  private:
    DeckFrame deckFrame_;
};

#endif
