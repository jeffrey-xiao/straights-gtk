#ifndef SUBJECT_H
#define SUBJECT_H

#include <unordered_set>

class Observer;

class Subject {
  public:
    void addObserver(Observer *);
  protected:
    void notify();
  private:
    std::unordered_set<Observer *> observers_;
};

#endif
