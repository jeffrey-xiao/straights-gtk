#ifndef GRAPHICAL_USER_INTERFACE_H
#define GRAPHICAL_USER_INTERFACE_H

#include <array>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/window.h>

#include "Observer.h"
#include "StraightsWindow.h"

class Command;
class GameController;
class StraightsWindow;

class StraightsGui : public Gtk::Application, public Observer {
  // GUI that shows a game of straights
  public:
    explicit StraightsGui(GameController *gameController);
    // ensures: initializes this to a GUI that represents an empty board of straights

    virtual ~StraightsGui();
    // modifies: this
    // ensures: this no longer exists, owned memory is freed

    void update() override;
    // modifies: this
    // ensures: GUI is updated to reflect the state of the game

  protected:
    void on_activate() override;

  private:
    bool isRunning_;
    GameController *gameController_;
    StraightsWindow window_;
    std::array<Gtk::CheckButton*, PLAYER_COUNT> playerTypeButtons_;

    void openPlayerTypesDialog();
};

#endif
