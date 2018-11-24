#include "PlayerFrame.h"
#include "GameController.h"

PlayerFrame::PlayerFrame(const std::string &name) : Gtk::Frame(), name_(name) {
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

std::string focusedMarkup(const std::string &text) {
  return "<span foreground=\"blue\">" + text + "</span>";
}

void PlayerFrame::setFocus(bool isFocus) {
  if (isFocus) {
    titleLabel_.set_markup(focusedMarkup(name_));
  } else {
    titleLabel_.set_text(name_);
  }
}

void PlayerFrame::setPoints(int points, bool isFocus) {
  if (isFocus) {
    pointsLabel_.set_markup(focusedMarkup(std::to_string(points) + " points"));
  } else {
    pointsLabel_.set_text(std::to_string(points) + " points");
  }
}

void PlayerFrame::setDiscards(int discards, bool isFocus) {
  if (isFocus) {
    discardsLabel_.set_markup(focusedMarkup(std::to_string(discards) + " discards"));
  } else {
    discardsLabel_.set_text(std::to_string(discards) + " discards");
  }
}

void PlayerFrame::setName(std::string name) {
  name_ = name;
}
