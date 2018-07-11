#include "Card.h"
#include "CardButton.h"
#include "HandFrame.h"

#include <gtkmm/frame.h>
#include <iostream>

const std::string CARD_IMG_PREFIX = "./img/";
const std::string CARD_IMG_SUFFIX = ".png";
const std::string NOTHING_IMG = CARD_IMG_PREFIX + "nothing.png";
const Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);

CardButton::CardButton(HandFrame* handFrame): handFrame_(handFrame),
  card_(SEVEN_OF_SPADES), image_(Gtk::Image(NOTHING_IMG))
{
  set_image(image_);
}

void CardButton::setCard(Card card) {
  card_ = card;
  image_ = Gtk::Image(CARD_IMG_PREFIX + card.getString() + CARD_IMG_SUFFIX);
  set_image(image_);
}

void CardButton::reset() {
  card_ = SEVEN_OF_SPADES;
  image_ = Gtk::Image(NOTHING_IMG);
  set_image(image_);
}

void CardButton::on_clicked() {
  handFrame_->executeCommand(card_);
}

