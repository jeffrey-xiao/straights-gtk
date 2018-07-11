#include "MenuFrame.h"
#include "StraightsGuiComponent.h"

MenuFrame::MenuFrame(StraightsGuiComponent *parent): Gtk::Frame("Menu Frame"),
  StraightsGuiComponent(parent), newGameButton_("New Game With Seed:"), quitButton_("Quit Game"),
  rageButton_("Rage")
{
  add(contents_);
  contents_.pack_start(newGameButton_);
  contents_.pack_start(seedEntry_);
  contents_.pack_start(quitButton_);
  contents_.pack_start(rageButton_);
  show_all_children();
}
