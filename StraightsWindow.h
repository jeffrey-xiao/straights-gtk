#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H

#include "BoardFrame.h"
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
    BoardFrame boardFrame_;
    MenuFrame menuFrame_;

    Gtk::Box playerContents_;
    std::vector<PlayerFrame> playerFrames_;

    HandFrame handFrame_;
};

#endif
