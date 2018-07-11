#include "HandFrame.h"

#include <gtkmm/button.h>

const int HAND_SIZE = 13;

HandFrame::HandFrame(): Gtk::Frame("Hand Frame") {
  hand_.resize(HAND_SIZE);

  add(contents_);
  for(Gtk::Button &c : hand_) {
    contents_.pack_start(c);
  }
  show_all_children();
}
