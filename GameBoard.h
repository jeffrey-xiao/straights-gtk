#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Straight.h"

#include <iostream>
#include <vector>

class Card;

class GameBoard {
  // Represents the played cards in a game of Straights
  // Specification Fields:
  //   clubs = clubs played on board
  //   diamonds = diamonds played on board
  //   hearts = hearts played on board
  //   spades = spades played on board

  std::vector<Straight> straights_;

 public:
  GameBoard();
  // ensures: initializes this to a GameBoard with no cards played

  void resetBoard();
  // ensures: resets this to a GameBoard with no cards played

  bool canPlayCard(Card card) const;
  // returns: true if card is a valid play on the board
  //          false if card is not a valid play on the board

  void playCard(Card card);
  // requires: canPlayCard(card)
  // ensures: this represents this@pre with card played

  void undoMove(Card card);
  // modifies: this
  // ensures: Card is not on the end of a straight

  bool hasCard(Card card) const;
  // returns: true if the card exists on the board

  friend std::ostream &operator<<(std::ostream &out, const GameBoard &gameBoard);
  // modifies: out
  // ensures: out = out@pre + clubs + \n + diamonds + \n + hearts + \n + spades + \n
  // returns: out
};

#endif
