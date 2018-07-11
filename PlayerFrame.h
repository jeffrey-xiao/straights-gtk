#ifndef PLAYER_FRAME_H
#define PLAYER_FRAME_H

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/frame.h"
#include "gtkmm/label.h"

#include <string>

class GameController;

class PlayerFrame : public Gtk::Frame {
  public:
    explicit PlayerFrame(const std::string&);
    virtual ~PlayerFrame() = default;

    void setFocus(bool);
    void setPoints(int, bool = false);
    void setDiscards(int, bool = false);

  private:
    std::string name_;
    Gtk::VBox contents_;
    Gtk::Label pointsLabel_, discardsLabel_, titleLabel_;
};

#endif
