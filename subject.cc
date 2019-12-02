#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>

using namespace std;

void Subject::attach(Observer *observer) {
    shared_ptr<Observer> ObPtr{ shared_ptr<Observer> {observer} };
    observers.emplace_back(ObPtr);
}

void Subject::notifyObservers() {
    for (auto &observer : observers) {
        observer->notify(*this);
    }
}

void Subject::remove() {
    observers.pop_back();
}

Subject::~Subject() {}