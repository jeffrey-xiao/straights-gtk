#ifndef MENU_FRAME_H
#define MENU_FRAME_H

#include "StraightsGuiComponent.h"

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>

class MenuFrame : public Gtk::Frame, public StraightsGuiComponent {
  public:
    explicit MenuFrame(StraightsGuiComponent *);

  private:
    Gtk::Box contents_;
    Gtk::Button newGameButton_, quitButton_, rageButton_;
    Gtk::Entry seedEntry_;
};

#endif
