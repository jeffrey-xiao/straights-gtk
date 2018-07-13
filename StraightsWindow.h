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
  // Window that shows a game of straights
  // Specification Fields:
  //   players = the frames that represents the scores and discards of all players
  //   game = the game of straights the board is monitoring

  public:
    explicit StraightsWindow(GameController *);
    // ensures: initializes this to an window representing a new game of straights
    //          the window monitors the game managed by the specified GameController

    virtual ~StraightsWindow();
    // modifies: this
    // ensures: this no longer exists, owned memory is freed

    void update() override;
    // modifies: this
    // ensures: players frames are updated to reflect the state of the game

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
