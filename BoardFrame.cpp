#include "Card.h"
#include "BoardFrame.h"
#include "StraightsGuiComponent.h"

BoardFrame::BoardFrame(StraightsGuiComponent *parent): Gtk::Frame("Cards on the table"),
  StraightsGuiComponent(parent)
{
  add(contents_);

  contents_.set_spacing(5);
  for (size_t i = 0; i < SUIT_COUNT; i++) {
    contents_.pack_start(straightBoxes_[i]);
    straightBoxes_[i].set_spacing(10);
  }

  for (size_t i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
    cardImages_[i].set("img/nothing.png");
    straightBoxes_[i / RANK_COUNT].pack_start(cardImages_[i]);
  }

  for (size_t i = 0; i < SUIT_COUNT; i++) {
    straightBoxes_[i].show_all_children();
  }

  show_all_children();
}
