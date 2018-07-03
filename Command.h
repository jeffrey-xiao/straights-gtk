#ifndef COMMAND_H
#define COMMAND_H

#include "Card.h"
#include <istream>

enum Type { PLAY, DISCARD, DECK, QUIT, RAGEQUIT, BAD_COMMAND };

struct Command{
	Type type;
	Card card;
	
	Command() : type(BAD_COMMAND), card(SPADE, ACE) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif
