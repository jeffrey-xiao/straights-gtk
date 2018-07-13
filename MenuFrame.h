#ifndef MENU_FRAME_H
#define MENU_FRAME_H

#include "Observer.h"

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/spinbutton.h>

class GameController;

class MenuFrame : public Gtk::Frame, public Observer {
  // Frame that shows the avaiable menu buttons of a game of straights
  // Specification Fields:
  //   game = the game of straights the menu is monitoring

  public:
    explicit MenuFrame(GameController *);
    // modifies: this
    // ensures: initializes this to an Menu for a new game of straights,
    //          this is added as an observer to gameController

    virtual ~MenuFrame() = default;
    // modifies: this
    // ensures: this no longer exists, owned memory is freed

    void update() override;
    // modifies: this
    // ensures: sets valid buttons as clickable/unclickable depending on
    //          the state of the game

  private:
    GameController *gameController_;
    Gtk::ButtonBox contents_;
    Gtk::Box newGameBox_;
    Gtk::Button newGameButton_, quitButton_, rageButton_;
    Gtk::SpinButton seedEntry_;

    void onNewGameButtonClick();
    void onRageButtonClick();
    void onQuitButtonClick();
};

#endif
