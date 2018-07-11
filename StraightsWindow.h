#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H

#include "DeckFrame.h"
#include "MenuFrame.h"
#include "PlayerFrame.h"
#include "HandFrame.h"

#include <gtkmm/applicationwindow.h>
#include <vector>

class GraphicalUserInterface;

class StraightsWindow : public Gtk::ApplicationWindow {
  public:
    StraightsWindow(GraphicalUserInterface *);

  private:
    GraphicalUserInterface *root_;

    Gtk::VBox contents_;
    MenuFrame menuFrame_;
    DeckFrame deckFrame_;

    Gtk::Box playerContents_;
    std::vector<PlayerFrame> playerFrames_;

    HandFrame handFrame_;
};

#endif
