#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>
#include <memory>

class Info;
class Observer;

class Subject{
	std::vector<std::unique_ptr<Observer>> observers;
    public:
	void attach(Observer *observer);
    void remove();
    void clear();
	void notifyObservers() const;
	virtual Info *getInfo() const = 0;
};

#endif
