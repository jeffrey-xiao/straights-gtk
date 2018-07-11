#include "GameController.h"
#include "GraphicalUserInterface.h"
#include "StraightsWindow.h"

#include <gtkmm/main.h>
#include <gtkmm/applicationwindow.h>

GraphicalUserInterface::GraphicalUserInterface(): window_(this) {}

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
  add_window(window_);
  window_.present();
}
