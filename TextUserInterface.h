#ifndef TEXTUSERINTERFACE_H
#define TEXTUSERINTERFACE_H

#include "Observer.h"

class Game;

class TextUserInterface : public Observer {
  public:
    void update() override;
    void setGame(Game* game);

  private:
    Game* game_;
    void getUserCommand();
};

#endif
