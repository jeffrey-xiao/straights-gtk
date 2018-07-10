#ifndef MENU_FRAME_H
#define MENU_FRAME_H

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>

class MenuFrame : public Gtk::Frame {
  public:
    MenuFrame();

  private:
    Gtk::Box contents_;
    Gtk::Button newGameButton_, quitButton_;
    Gtk::Entry seedEntry_;
};

#endif
