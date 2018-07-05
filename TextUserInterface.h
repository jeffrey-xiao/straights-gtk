#ifndef TEXTUSERINTERFACE_H
#define TEXTUSERINTERFACE_H

#include "Observer.h"

class GameController;

class TextUserInterface : public Observer {
  public:
    void update() override;
    void setGameController(GameController* gameController);

  private:
    GameController* gameController_;
    void getUserCommand();
};

#endif
