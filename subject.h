#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>
#include <memory>

class Observer;
class Info;

class Subject{
	std::vector<unique_ptr<Observer>> observers;
    public:
	void attach(Observer *observer);
    void clear();
	void notifyObservers() const;
	virtual Info getInfo() const = 0;
};

#endif
