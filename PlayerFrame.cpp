#include "PlayerFrame.h"
#include "StraightsGuiComponent.h"

PlayerFrame::PlayerFrame(StraightsGuiComponent *parent, std::string name): Gtk::Frame(name),
  StraightsGuiComponent(parent)
{
  add(contents_);
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
