#ifndef TEXTUSERINTERFACE_H
#define TEXTUSERINTERFACE_H

#include "Observer.h"

class GameController;

class TextUserInterface : public Observer {
  public:
    void update() override;
    void setGameController(GameController* gameController);
    void startGame();

  private:
    GameController* gameController_;
};

#endif
