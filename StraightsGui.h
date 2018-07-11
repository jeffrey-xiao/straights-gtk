#ifndef GRAPHICAL_USER_INTERFACE_H
#define GRAPHICAL_USER_INTERFACE_H

#include <gtkmm/window.h>

#include "Observer.h"
#include "StraightsWindow.h"

class Command;
class GameController;
class StraightsWindow;

class StraightsGui : public Gtk::Application, public Observer {
  public:
    explicit StraightsGui(GameController *gameController);
    virtual ~StraightsGui() = default;

    void update() override;
    void setGameController(GameController *gameController);
    void startGame();

  protected:
    void on_activate() override;

  private:
    bool isRunning_;
    GameController *gameController_;
    StraightsWindow window_;
};

#endif
