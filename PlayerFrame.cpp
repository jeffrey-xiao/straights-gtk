#include "PlayerFrame.h"

PlayerFrame::PlayerFrame(std::string name): Gtk::Frame(name), rageButton_("Rage!") {
  add(contents_);
  contents_.pack_start(rageButton_);
  contents_.pack_start(pointsLabel_);
  contents_.pack_start(discardsLabel_);
  setPoints(0);
  setDiscards(0);
  show_all_children();
}

void PlayerFrame::setPoints(int points) {
  pointsLabel_.set_text(std::to_string(points) + " points");
}

void PlayerFrame::setDiscards(int discards) {
  discardsLabel_.set_text(std::to_string(discards) + " discards");
}
