#ifndef HAND_FRAME_H
#define HAND_FRAME_H

#include "CardButton.h"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>

#include <vector>

class HandFrame : public Gtk::Frame {
  public:
    HandFrame();

  private:
    Gtk::Box contents_;
    std::vector<CardButton> hand_;
};

#endif
