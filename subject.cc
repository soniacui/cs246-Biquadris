#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach(Observer *observer) {
    observers.emplace_back(observer);
}

void Subject::notifyObservers() {
    for (auto &observer : observers) {
        observer->notify(*this);
    }
}