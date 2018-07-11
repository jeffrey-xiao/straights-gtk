#include "Command.h"
#include "GameController.h"
#include "MenuFrame.h"

MenuFrame::MenuFrame(GameController *gameController): Gtk::Frame("Menu Frame"),
  gameController_(gameController), newGameButton_("New Game With Seed:"), quitButton_("Quit Game"),
  rageButton_("Rage")
{
  gameController_->addObserver(this);
  add(contents_);
  contents_.set_layout(Gtk::BUTTONBOX_START);
  contents_.set_spacing(10);

  contents_.pack_start(newGameBox_);
  newGameBox_.pack_start(newGameButton_);
  newGameBox_.pack_start(seedEntry_);

  contents_.pack_start(rageButton_);
  contents_.pack_start(quitButton_);

  rageButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuFrame::onRageButtonClick));
  quitButton_.signal_clicked().connect(sigc::mem_fun(*this, &MenuFrame::onQuitButtonClick));

  show_all_children();
}

void MenuFrame::update() {}

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
