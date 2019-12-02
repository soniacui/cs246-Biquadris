#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>
#include <memory>
#include "info.h"

class Observer;

class Subject{
public: //change back!
	std::vector<std::shared_ptr<Observer>> observers;
    //public:
	void attach(Observer *observer);
    void remove();
    void clear();
	void notifyObservers();
	virtual std::shared_ptr<BoardInfo> getInfo() const;
    virtual std::shared_ptr<TetrominoInfo> getTetroInfo();
    virtual ~Subject() = 0;
};

#endif
