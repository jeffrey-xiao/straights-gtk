#ifndef TEXTUSERINTERFACE_H
#define TEXTUSERINTERFACE_H

#include "Observer.h"

class GameController;

class StraightsTui : public Observer {
  // A terminal UI for a game of Straights
  // Specification Fields:
  //   game = representation for the game of straights
  //   controller = object that handles communication to the game
 public:
  explicit StraightsTui(GameController *gameController);
  // ensures: initializes this to a new StraightsTui with a specified game controller

  virtual ~StraightsTui() = default;
  // ensures: this no longer exists; owned memory is deallocated

  void update() override;
  // modifies: cout
  // ensures: cout is updated in response to changes in the game

 private:
  GameController *gameController_;
};

#endif
