#ifndef PLAYER_FRAME_H
#define PLAYER_FRAME_H

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/frame.h"
#include "gtkmm/label.h"

#include <string>

class GameController;

class PlayerFrame : public Gtk::Frame {
  // Frame that shows the statistics for a specific player. More specifically, the frame displays
  // the points and discards of a particular player.

 public:
  explicit PlayerFrame(const std::string &);
  // ensures: initializes this to an empty PlayerFrame

  virtual ~PlayerFrame() = default;
  // modifies: this
  // ensures: this no longer exists, owned memory is freed

  void setFocus(bool isFocus);
  // modifies: this
  // ensures: the focus of this is set to isFocus

  void setPoints(int points, bool isFocus = false);
  // modifies: this
  // ensures: the focus of the points label is set to isFocus; the points displayed is set

  void setDiscards(int discards, bool isFocus = false);
  // modifies: this
  // ensures: the focus of the discards label is set to isFocus; the number of discards is set

  void setName(std::string);
  // modifies: this
  // ensures: the label of the frame is set to the specified string

 private:
  std::string name_;
  Gtk::VBox contents_;
  Gtk::Label pointsLabel_, discardsLabel_, titleLabel_;
};

#endif
