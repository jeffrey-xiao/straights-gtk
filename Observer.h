#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
  // Abstract base class for the Subject-Observer Pattern
  public:
    virtual void update() = 0;
    // ensures: Observer is properly updated in response to subject changes
};

#endif
