#ifndef COMMAND_H
#define COMMAND_H

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };
// enum representing the type of command

struct Command {
  // Represents a game Command with a type and a card
  // Specification Fields:
  //   type = type of command
  //   card = card associated with a command
  Type type;
  Card card;

  Command(): type(BAD_COMMAND), card(SPADE, ACE) {}
  // ensures: initializes this to Command with type BAD_COMMAND and
  //          card Ace of Spades
};

std::istream &operator>>(std::istream &in, Command &c);
  // TO DO
  // modifies: in, c
  // ensures: in@pre = commandString + cardString (only if commandString = play, disard) + in,
  //          c.type = commandString, c.card = cardString
  // returns: in

#endif
