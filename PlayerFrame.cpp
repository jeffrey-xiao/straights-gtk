#include "GameController.h"
#include "PlayerFrame.h"

PlayerFrame::PlayerFrame(const std::string &name): Gtk::Frame(), name_(name) {
  set_border_width(4);
  add(contents_);
  contents_.pack_start(pointsLabel_);
  contents_.pack_start(discardsLabel_);
  titleLabel_.set_text(name_);
  set_label_widget(titleLabel_);
  setPoints(0);
  setDiscards(0);
  show_all_children();
}

void PlayerFrame::setFocus(bool isFocus) {
  if(isFocus)
    titleLabel_.set_markup("<b>" + name_ + "</b>");
  else
    titleLabel_.set_text(name_);
}

void PlayerFrame::setPoints(int points, bool isFocus) {
  if(isFocus)
    pointsLabel_.set_markup("<b>" + std::to_string(points) + " points" + "</b>");
  else
    pointsLabel_.set_text(std::to_string(points) + " points");
}

void PlayerFrame::setDiscards(int discards, bool isFocus) {
  if(isFocus)
    discardsLabel_.set_markup("<b>" + std::to_string(discards) + " discards" + "</b>");
  else
    discardsLabel_.set_text(std::to_string(discards) + " discards");
}
