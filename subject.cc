#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <iostream> ////////////rem

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

void Subject::clear() {
	observers.clear();
}

void Subject::remove(int size) {
    if (size == 1) {
        observers[1]->popped = true;
    }
    else
        observers.back()->popped = true;
}

Subject::~Subject() {}
