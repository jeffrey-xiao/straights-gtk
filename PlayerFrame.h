#ifndef PLAYER_FRAME_H
#define PLAYER_FRAME_H

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/frame.h"
#include "gtkmm/label.h"

class GameController;

class PlayerFrame : public Gtk::Frame {
  public:
    explicit PlayerFrame(const std::string&);
    virtual ~PlayerFrame() = default;

    void setPoints(int);
    void setDiscards(int);

  private:
    Gtk::VBox contents_;
    Gtk::Label pointsLabel_, discardsLabel_;
};

#endif
