#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>

class Observer;
class Info;

class Subject{
	std::vector<Observer*> observers;
    public:
	void attach(Observer *observer);
	void notifyObservers() const;
	virtual Info getInfo() const = 0;
};

#endif
