#include "GameController.h"
#include "GraphicalUserInterface.h"
#include "StraightsWindow.h"

#include <gtkmm/main.h>
#include <gtkmm/applicationwindow.h>

GraphicalUserInterface::GraphicalUserInterface() : Gtk::Application() {}

void GraphicalUserInterface::update() {
  Game::GameState gameState = gameController_->getGameState();

  switch (gameState) {
    case Game::GameState::ROUND_START:
      this->run();
      return;
  }
}

void GraphicalUserInterface::startGame() {
  gameController_->startGame();
}

void GraphicalUserInterface::setGameController(GameController *gameController) {
  gameController_ = gameController;
}

void GraphicalUserInterface::on_activate() {
  auto straightsWindow = new StraightsWindow(this);
  add_window(*straightsWindow);
  straightsWindow->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this, &GraphicalUserInterface::on_hide_window), straightsWindow));
  straightsWindow->present();
}

void GraphicalUserInterface::on_hide_window(Gtk::Window* window) {
  delete window;
}
