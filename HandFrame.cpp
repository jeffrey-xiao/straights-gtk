#include "Card.h"
#include "GameController.h"
#include "HandFrame.h"

#include <gtkmm/button.h>

HandFrame::HandFrame(GameController *gameController): Gtk::Frame("Hand Frame"),
  gameController_(gameController)
{
  gameController_->addObserver(this);
  hand_.resize(RANK_COUNT);

  add(contents_);
  for(Gtk::Button &c : hand_) {
    contents_.pack_start(c);
  }
  contents_.set_spacing(10);
  show_all_children();
}

void HandFrame::update() {

}
