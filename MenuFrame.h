#ifndef MENU_FRAME_H
#define MENU_FRAME_H

#include "Observer.h"

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>

class GameController;

class MenuFrame : public Gtk::Frame, public Observer {
  public:
    explicit MenuFrame(GameController *);
    virtual ~MenuFrame() = default;
    void update() override;

  private:
    GameController *gameController_;
    Gtk::ButtonBox contents_;
    Gtk::Box newGameBox_;
    Gtk::Button newGameButton_, quitButton_, rageButton_;
    Gtk::Entry seedEntry_;

    void onRageButtonClick();
    void onQuitButtonClick();
};

#endif
