#include "GameController.h"
#include "Player.h"
#include "StraightsWindow.h"

#include <gtkmm/messagedialog.h>
#include <vector>

StraightsWindow::StraightsWindow(GameController *gameController): gameController_(gameController),
  boardFrame_(gameController), menuFrame_(gameController), handFrame_(gameController)
{
  gameController->addObserver(this);
  set_title("Straights");
  set_default_size(400, 400);

  add(contents_);
  contents_.pack_start(menuFrame_);
  contents_.pack_start(boardFrame_);

  contents_.pack_start(playerContents_);
  playerFrames_.reserve(PLAYER_COUNT);
  for (size_t i = 0; i < PLAYER_COUNT; i++) {
    playerFrames_.push_back(new PlayerFrame("Player " + std::to_string(i + 1)));
    playerContents_.pack_start(*playerFrames_[i]);
  }

  contents_.pack_start(handFrame_);

  show_all_children();
}

StraightsWindow::~StraightsWindow() {
  for (PlayerFrame *playerFrame : playerFrames_) {
    delete playerFrame;
  }
}

void StraightsWindow::update() {
  Game::GameState gameState = gameController_->getGameState();
  std::vector<Player> players = gameController_->getPlayers();

  int currentPlayer = -1;

  if (gameState != Game::GameState::GAME_START) {
    currentPlayer = gameController_->getCurrentPlayerId() - 1;
  }

  for (size_t i = 0; i < players.size(); i++) {
    bool isFocus = (currentPlayer == (int)i);
    playerFrames_[i]->setFocus(isFocus);
    playerFrames_[i]->setPoints(players[i].getScore(), isFocus);
    playerFrames_[i]->setDiscards(players[i].getDiscardedCards().size(), isFocus);
  }


  if (gameState == Game::GameState::ROUND_END) {
    Gtk::MessageDialog roundEndDialog(*this, "Round Over.");
    std::string secondaryText = "";
    for (size_t i = 0; i < players.size(); i++) {
      secondaryText += "Player " + std::to_string(players[i].getId()) + " discarded";
      if (players[i].getDiscardedCards().empty()) {
        secondaryText += " nothing.\n";
      } else {
        for (const Card &card : players[i].getDiscardedCards()) {
          secondaryText += " " + card.getString();
        }
        secondaryText += ".\n";
      }

      int score = players[i].getScore();
      int roundScore = players[i].getRoundScore();
      secondaryText += "Player " + std::to_string(players[i].getId()) + " has ";
      secondaryText += std::to_string(score) + " + " + std::to_string(roundScore) + " = ";
      secondaryText += std::to_string(score + roundScore) + " points.\n";
    }
    roundEndDialog.set_secondary_text(secondaryText);
    roundEndDialog.run();
  } else if (gameState == Game::GameState::GAME_END) {
    Gtk::MessageDialog gameEndDialog(*this, "Game Over.");
    std::string secondaryText = "";

    std::vector<Player> winners = gameController_->getWinners();
    for (Player winner : winners) {
      secondaryText += "Player " + std::to_string(winner.getId()) + " wins with ";
      secondaryText += std::to_string(winner.getScore()) + " points.\n";
    }
    gameEndDialog.set_secondary_text(secondaryText);
    gameEndDialog.run();
  }
}
