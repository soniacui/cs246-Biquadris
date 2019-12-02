#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <iostream> ////////////rem

using namespace std;

void Subject::attach(Observer *observer) {
	//cout << "size: " << observers.size() <<endl;
    shared_ptr<Observer> ObPtr{ shared_ptr<Observer> {observer} };
    observers.emplace_back(ObPtr);
    //cout << "size2: " << observers.size() <<endl;
}

void Subject::notifyObservers() {
    for (auto &observer : observers) {
        observer->notify(*this);
    }
}

void Subject::clear() {
	observers.clear();
}

void Subject::remove() {
    observers.pop_back();
}

Subject::~Subject() {}
