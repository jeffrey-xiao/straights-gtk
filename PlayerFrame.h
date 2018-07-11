#ifndef PLAYER_FRAME_H
#define PLAYER_FRAME_H

#include "Observer.h"

#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/frame.h"
#include "gtkmm/label.h"

class GameController;

class PlayerFrame : public Gtk::Frame, public Observer {
  public:
    explicit PlayerFrame(GameController *, std::string);
    virtual ~PlayerFrame() = default;
    void update() override;

    void setPoints(int);
    void setDiscards(int);

  private:
    GameController *gameController_;
    Gtk::VBox contents_;
    Gtk::Label pointsLabel_, discardsLabel_;
};

#endif
