#ifndef HAND_FRAME_H
#define HAND_FRAME_H

#include "CardButton.h"
#include "Observer.h"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>

#include <vector>

class GameController;

class HandFrame : public Gtk::Frame, public Observer {
  public:
    explicit HandFrame(GameController *);
    virtual ~HandFrame() = default;
    void update() override;

  private:
    GameController *gameController_;
    Gtk::Box contents_;
    std::vector<CardButton> hand_;
};

#endif
