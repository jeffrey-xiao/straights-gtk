#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "Card.h"

#include <gtkmm/image.h>
#include <gtkmm/button.h>

class CardButton : public Gtk::Button {
  public:
    CardButton();
    void setCard(Card card);
    void reset();

  private:
    Card card_;
    Gtk::Image image_;
};

#endif
