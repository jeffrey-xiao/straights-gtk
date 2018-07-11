#include "Card.h"
#include "HandFrame.h"

#include <gtkmm/button.h>


HandFrame::HandFrame(StraightsGuiComponent *parent): Gtk::Frame("Hand Frame"),
  StraightsGuiComponent(parent)
{
  hand_.resize(RANK_COUNT);

  add(contents_);
  for(Gtk::Button &c : hand_) {
    contents_.pack_start(c);
  }
  contents_.set_spacing(10);
  show_all_children();
}
