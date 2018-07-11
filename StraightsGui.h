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
  public:
    explicit StraightsGui(GameController *gameController);
    virtual ~StraightsGui();
    void update() override;

  protected:
    void on_activate() override;

  private:
    bool isRunning_;
    GameController *gameController_;
    StraightsWindow window_;
    std::array<Gtk::CheckButton*, 4> playerTypeButtons_;

    void openPlayerTypesDialog();
};

#endif
