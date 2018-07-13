#ifndef HAND_FRAME_H
#define HAND_FRAME_H

#include "CardButton.h"
#include "Observer.h"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>

#include <vector>

class GameController;

class HandFrame : public Gtk::Frame, public Observer {
  // Frame that shows the hand of the current player (reflects game state)
  // Specification Fields:
  //   cards = the cards the HandFrame represents
  //   game = the game of straights the is monitoring

  public:
    explicit HandFrame(GameController *gameController);
    // modifies: this
    // ensures: initializes this to a hand with 13 empty card slots
    //          this is added as an observer to gameController

    virtual ~HandFrame() = default;
    // modifies: this
    // ensures: this no longer exists, owned memory is freed

    void update() override;
    // modifies: this
    // ensures: the cards in the hand represents the cards of current player

    void executeCommand(Card);
    // requires: Card is a card in the current players hand
    // ensures: signals to the game that the current card is being played/discarded

  private:
    GameController *gameController_;
    Gtk::Box contents_;
    std::vector<CardButton> hand_;
    bool isDiscard_;
};

#endif
