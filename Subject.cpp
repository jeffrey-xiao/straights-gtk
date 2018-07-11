#include "Observer.h"
#include "Subject.h"

#include <unordered_set>

void Subject::addObserver(Observer *observer) {
  observers_.insert(observer);
}

void Subject::notify() {
  for (auto observer : observers_) {
    observer->update();
  }
}

