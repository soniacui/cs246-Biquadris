#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>

using namespace std;

void Subject::attach(Observer *observer) {
    unique_ptr<Observer> ObPtr{ unique_ptr<Observer> {observer} };
    observers.emplace_back(ObPtr);
}

void Subject::notifyObservers() const {
    for (auto &observer : observers) {
        observer->notify(*this);
    }
}

void Subject::remove() {
    observers.pop_back();
}

Subject::~Subject() {}