#ifndef HAND_FRAME_H
#define HAND_FRAME_H

#include "CardButton.h"
#include "StraightsGuiComponent.h"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>

#include <vector>

class HandFrame : public Gtk::Frame, public StraightsGuiComponent {
  public:
    explicit HandFrame(StraightsGuiComponent *);

  private:
    Gtk::Box contents_;
    std::vector<CardButton> hand_;
};

#endif
