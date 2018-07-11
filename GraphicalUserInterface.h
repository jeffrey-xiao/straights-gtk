#ifndef GRAPHICAL_USER_INTERFACE_H
#define GRAPHICAL_USER_INTERFACE_H

#include <gtkmm/window.h>

#include "Observer.h"
#include "StraightsWindow.h"

class GameController;
class StraightsWindow;

class GraphicalUserInterface : public Gtk::Application, public Observer {
  public:
    GraphicalUserInterface();
    virtual ~GraphicalUserInterface() = default;

    void update() override;
    void setGameController(GameController *gameController);
    void startGame();

  protected:
    void on_activate() override;

  private:
    GameController *gameController_;
    StraightsWindow window_;
};

#endif
