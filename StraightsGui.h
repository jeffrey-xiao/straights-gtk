#ifndef GRAPHICAL_USER_INTERFACE_H
#define GRAPHICAL_USER_INTERFACE_H

#include <gtkmm/window.h>

#include "Observer.h"
#include "StraightsWindow.h"
#include "StraightsGuiComponent.h"

class Command;
class GameController;
class StraightsWindow;

class StraightsGui : public Gtk::Application, public Observer, public StraightsGuiComponent {
  public:
    StraightsGui();
    virtual ~StraightsGui() = default;

    void update() override;
    void notify(Command);
    void setGameController(GameController *gameController);
    void startGame();

  protected:
    void on_activate() override;

  private:
    GameController *gameController_;
    StraightsWindow window_;
};

#endif
