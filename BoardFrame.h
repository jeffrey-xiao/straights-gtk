#ifndef DECK_FRAME_H
#define DECK_FRAME_H

#include "Card.h"

#include <array>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/frame.h>

class BoardFrame : public Gtk::Frame {
  public:
    BoardFrame();

  private:
    Gtk::VBox contents_;
    std::array<Gtk::Box, SUIT_COUNT> straightBoxes_;
    std::array<Gtk::Image, SUIT_COUNT * RANK_COUNT> cardImages_;
};

#endif
