#ifndef TEXTUSERINTERFACE_H
#define TEXTUSERINTERFACE_H

#include "Observer.h"

class GameController;

class TextUserInterface : public Observer {
  // A terminal UI for a game of Straights
  // Specification Fields:
  //   game = representation for the game of straights
  //   controller = object that handles communication to the game
  public:
    virtual ~TextUserInterface() = default;
    // ensures: this no longer exists; owned memory is deallocated

    void update() override;
    // modifies: cout
    // ensures: cout is updated in response to changes in the game

    void setGameController(GameController* gameController);
    // requires: gameController points to a valid GameController
    // ensures: controller = gameController

    void startGame();
    // requires: gameController_ is a valid controller
    // modifies: cin, cout
    // ensures: this continues to read game commands from cin and prints
    //          the game changes to cout until the game is over

  private:
    GameController *gameController_;
};

#endif
