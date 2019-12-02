#ifndef _SUBJECT_
#define _SUBJECT_
#include <vector>
#include <memory>
#include "info.h"

class Observer;

class Subject{
	std::vector<std::unique_ptr<Observer>> observers;
    public:
	void attach(Observer *observer);
    void remove();
    void clear();
	void notifyObservers() const;
	virtual std::unique_ptr<BoardInfo> getInfo() const;
    virtual std::unique_ptr<TetrominoInfo> getTetroInfo() const;
    virtual ~Subject();
};

#endif
