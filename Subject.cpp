#include "Subject.h"
#include "Observer.h"

#include <vector>

Subject::~Subject() {}

void Subject::addObserver(Observer *observer) {
  observers_.push_back(observer);
}

void Subject::notify() {
  for (auto observer : observers_) {
    observer->update();
  }
}
