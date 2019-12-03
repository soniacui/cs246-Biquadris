#ifndef _OBSERVER_
#define _OBSERVER_

class Subject;

class Observer{
    public:
	bool popped = false;
	virtual void notify(Subject &notifier) = 0; //reference to the Subject that notified this Observer
	virtual ~Observer() = default; //default destructor, i.e. does nothing
};

#endif
