#ifndef GRAPHICAL_USER_INTERFACE_H
#define GRAPHICAL_USER_INTERFACE_H

#include <gtkmm/window.h>

#include "Observer.h"

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
    void on_hide_window(Gtk::Window* window);
};

#endif
