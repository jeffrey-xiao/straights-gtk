#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H

#include "DeckFrame.h"
#include "MenuFrame.h"
#include "PlayerFrame.h"

#include <gtkmm/applicationwindow.h>
#include <vector>

class GraphicalUserInterface;

class StraightsWindow : public Gtk::ApplicationWindow {
  public:
    StraightsWindow(GraphicalUserInterface *);

  private:
    GraphicalUserInterface *root_;

    Gtk::VBox contents_;
    DeckFrame deckFrame_;
    MenuFrame menuFrame_;

    Gtk::Box playerContents_;
    std::vector<PlayerFrame> playerFrames_;
};

#endif
