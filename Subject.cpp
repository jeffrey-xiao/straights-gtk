#include "Observer.h"
#include "Subject.h"

#include <vector>

void Subject::addObserver(Observer *observer) {
  observers_.push_back(observer);
}

void Subject::notify() {
  for (auto observer : observers_) {
    observer->update();
  }
}

