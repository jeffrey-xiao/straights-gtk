#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Straight.h"

#include <iostream>
#include <vector>

class Card;

class GameBoard {
  private:
    std::vector<Straight> straights_;

  public:
    GameBoard();

    void resetBoard();
    bool canPlayCard(Card) const;
    void playCard(Card);

    friend std::ostream& operator<<(std::ostream &, const GameBoard &);
};

#endif
