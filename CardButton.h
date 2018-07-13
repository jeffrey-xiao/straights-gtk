#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "Card.h"

#include <gtkmm/image.h>
#include <gtkmm/button.h>

class HandFrame;

class CardButton : public Gtk::Button {
  // Button that represents a card slot in the current player's hand
  // Specification Fields:
  //   card = the card the button is representing
  //   hand = the HandFrame the button sends signals to
  public:
    explicit CardButton(HandFrame *);
    // ensures: initializes this to a button representing an empty card slot
    //          this sends signals to the specified HandFrame

    void setCard(Card);
    // modifies: this
    // ensures: sets card to the card specified

    void setColor(Gdk::RGBA);
    // modifies: this
    // ensures: this button has a background color of the color specified

    void reset();
    // modifies: this
    // ensures: this is a button representing an empty card slot

    void on_clicked() override;
    // ensures: sends a signal to the hand, marking the card as being played or discarded

  private:
    HandFrame *handFrame_;
    Card card_;
    Gtk::Image image_;
};

#endif
