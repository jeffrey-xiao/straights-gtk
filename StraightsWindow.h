#ifndef STRAIGHTS_WINDOW_H
#define STRAIGHTS_WINDOW_H

#include "BoardFrame.h"
#include "HandFrame.h"
#include "MenuFrame.h"
#include "Observer.h"
#include "PlayerFrame.h"

#include <gtkmm/applicationwindow.h>
#include <vector>

class GameController;
class GraphicalUserInterface;

class StraightsWindow : public Gtk::ApplicationWindow, public Observer {
  public:
    explicit StraightsWindow(GameController *);
    virtual ~StraightsWindow();
    void update() override;

  private:
    GameController *gameController_;

    Gtk::VBox contents_;
    BoardFrame boardFrame_;
    MenuFrame menuFrame_;

    Gtk::Box playerContents_;
    std::vector<PlayerFrame*> playerFrames_;

    HandFrame handFrame_;
};

#endif
