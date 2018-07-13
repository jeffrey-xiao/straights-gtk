#include "Command.h"
#include "GameController.h"
#include "MenuFrame.h"

const int MAX_DIGITS = 11;
const int STEP_INCREMENT = 1;
const int PAGE_INCREMENT = 1;

MenuFrame::MenuFrame(GameController *gameController): Gtk::Frame(),
  gameController_(gameController), newGameButton_("New Game With Seed:"),
  quitButton_("Quit Game"), rageButton_("Rage"), undoButton_("Undo")
{
  set_border_width(6);
  gameController_->addObserver(this);
  add(contents_);
  contents_.set_layout(Gtk::BUTTONBOX_START);
  contents_.set_spacing(10);
  contents_.set_border_width(4);

  contents_.pack_start(newGameBox_);
  newGameBox_.pack_start(newGameButton_);
  newGameBox_.pack_start(seedEntry_);

  contents_.pack_start(rageButton_);
  contents_.pack_start(quitButton_);
  contents_.pack_start(undoButton_);

  newGameButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuFrame::onNewGameButtonClick));
  seedEntry_.set_range(INT_MIN, INT_MAX);
  seedEntry_.set_increments(STEP_INCREMENT, PAGE_INCREMENT);
  seedEntry_.set_width_chars(MAX_DIGITS);
  rageButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuFrame::onRageButtonClick));
  quitButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuFrame::onQuitButtonClick));
  undoButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuFrame::onUndoButtonClick));

  show_all_children();
}

void MenuFrame::update() {
  Game::GameState gameState = gameController_->getGameState();
  if (gameState == Game::GameState::HUMAN_INPUT) {
    rageButton_.set_sensitive(true);
  } else {
    rageButton_.set_sensitive(false);
  }

  if(gameController_->canUndoMove()) {
    undoButton_.set_sensitive(true);
  } else {
    undoButton_.set_sensitive(false);
  }
}

void MenuFrame::onNewGameButtonClick() {
  gameController_->setSeed(seedEntry_.get_value_as_int());
  gameController_->initGame();
}

void MenuFrame::onRageButtonClick() {
  Command command;
  command.type = RAGEQUIT;
  gameController_->executeCommand(command);
}


void MenuFrame::onQuitButtonClick() {
  Command command;
  command.type = QUIT;
  gameController_->executeCommand(command);
}

void MenuFrame::onUndoButtonClick() {
  gameController_->undoMove();
}
