#ifndef _TETROMINO_
#define _TETROMINO_
#include "observer.h"
#include "subject.h"
#include <vector>

class Info;

class Tetromino:public Subject, public Observer{
    protected:
        char type;
	    int speed;
	    int value;
	    bool isDeleted;
        vector<vector<int>> previously; //remembers last position for grid to clear
	    vector<vector<int>> absCoords;
	    vector<vector<char>> currGrid;
    public:
	    Tetromino(int speed, int value);
	    void move(string direction);
	    void rotate(string direction); //notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
	    void drop();
        void increaseSpeed(int increase);
        Info *getInfo() const override;
	    void notify(Subject &notifier) override; //cares only about when toDelete is not empty
	    virtual ~Tetromino() = 0; //default destructor, also make Tetromino abstract
};

class IBlock:public Tetromino{
    public:
        IBlock(int speed, int value, char type = 'I');
	    ~IBlock() override;
};

class JBlock:public Tetromino{
    public:
        JBlock(int speed, int value, char type = 'J');
        ~JBlock() override;
};

class LBlock:public Tetromino{
    public:
        LBlock(int speed, int value, char type = 'L');
        ~LBlock() override;
};

class OBlock:public Tetromino{
    public:
        OBlock(int speed, int value, char type = 'O');
        ~OBlock() override;
};

class SBlock:public Tetromino{
    public:
        SBlock(int speed, int value, char type = 'S');
        ~SBlock() override;
};

class ZBlock:public Tetromino{
    public:
        ZBlock(int speed, int value, char type = 'Z');
        ~ZBlock() override;
};

class TBlock:public Tetromino{
    public:
        TBlock(int speed, int value, char type = 'T');
        ~TBlock() override;
};

class StarBlock:public Tetromino{
    public:
        StarBlock(int speed, int value, char type = '*');
        ~StarBlock() override;
};
