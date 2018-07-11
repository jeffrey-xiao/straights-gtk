#include "Command.h"
#include "GameController.h"
#include "StraightsGui.h"
#include "StraightsWindow.h"

#include <gtkmm/main.h>
#include <gtkmm/applicationwindow.h>

StraightsGui::StraightsGui(): window_(this) {}

void StraightsGui::update() {
  Game::GameState gameState = gameController_->getGameState();

  switch (gameState) {
    case Game::GameState::ROUND_START:
      this->run();
      return;
  }
}

void StraightsGui::notify(Command command) {
  gameController_->executeCommand(command);
}

void StraightsGui::startGame() {
  gameController_->startGame();
}

void StraightsGui::setGameController(GameController *gameController) {
  gameController_ = gameController;
}

void StraightsGui::on_activate() {
  add_window(window_);
  window_.present();
}
