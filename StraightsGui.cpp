#include "Command.h"
#include "GameController.h"
#include "Player.h"
#include "StraightsGui.h"
#include "StraightsWindow.h"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dialog.h>
#include <gtkmm/main.h>

StraightsGui::StraightsGui(GameController *gameController): gameController_(gameController),
  window_(gameController)
{
  gameController_->addObserver(this);
  for (size_t i = 0; i < playerTypeButtons_.size(); i++) {
    playerTypeButtons_[i] = new Gtk::CheckButton("Human Player " + std::to_string(i + 1));
  }
}

StraightsGui::~StraightsGui() {
  for (Gtk::CheckButton *playerTypeButton : playerTypeButtons_) {
    delete playerTypeButton;
  }
}

void StraightsGui::update() {
  Game::GameState gameState = gameController_->getGameState();

  if (gameState == Game::GameState::GAME_START) {
    if (!isRunning_) {
      isRunning_ = true;
      this->run();
    } else {
      openPlayerTypesDialog();
    }
  } else if (gameState == Game::GameState::GAME_QUIT) {
    this->quit();
  }
}

void StraightsGui::on_activate() {
  add_window(window_);
  window_.present();
  openPlayerTypesDialog();
}

void StraightsGui::openPlayerTypesDialog() {
  Gtk::Dialog playerTypesDialog("Choose player types", window_);
  Gtk::Box *contentArea = playerTypesDialog.get_content_area();
  for (size_t i = 0; i < playerTypeButtons_.size(); i++) {
    contentArea->pack_start(*(playerTypeButtons_[i]));
  }
  contentArea->show_all_children();
  playerTypesDialog.add_button("Confirm", Gtk::ResponseType::RESPONSE_OK);
  playerTypesDialog.run();
  playerTypesDialog.hide();

  std::vector<PlayerType> playerTypes;
  playerTypes.reserve(4);
  for (size_t i = 0; i < 4; i++) {
    playerTypes.push_back(playerTypeButtons_[i]->get_active() ? PlayerType::HUMAN : PlayerType::COMPUTER);
  }
  gameController_->startGame(playerTypes);
}
