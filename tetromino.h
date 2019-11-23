#ifndef _TETROMINO_
#define _TETROMINO_
#include <vector>

class Info;
class Subject;

class Tetromino:public Subject, public Observer{
    protected:
	int speed;
	int value;
	bool isDeleted; //may not be necessary, if notify() removes elements from absCoords
	vector<vector<int>> absCoords;
	vector<vector<char>> currGrid;
    public:
	Tetromino(int speed, int value);
	void move(string direction);
	void rotate(string direction); //notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
	void drop();
	notify(Subject &notifier) override; //cares only about when toDelete is not empty
	virtual ~Tetromino() = 0; //default destructor, also make Tetromino abstract
};

class IBlock:public Tetromino{
	char type;
    public:
	IBlock(int speed, int value);
	Info getInfo() const override; //allows retrieval of type
	~IBlock() override;
};

class JBlock:public Tetromino{
        char type;
    public:
        JBlock(int speed, int value);
        Info getInfo() const override; //allows retrieval of type
        ~JBlock() override;
};

class LBlock:public Tetromino{
        char type;
    public:
        LBlock(int speed, int value);
        Info getInfo() const override; //allows retrieval of type
        ~LBlock() override;
};

class OBlock:public Tetromino{
        char type;
    public:
        OBlock(int speed, int value);
        Info getInfo() const override; //allows retrieval of type
        ~OBlock() override;
};

class SBlock:public Tetromino{
        char type;
    public:
        SBlock(int speed, int value);
        Info getInfo() const override; //allows retrieval of type
        ~SBlock() override;
};

class ZBlock:public Tetromino{
        char type;
    public:
        ZBlock(int speed, int value);
        Info getInfo() const override; //allows retrieval of type
        ~ZBlock() override;
};

class TBlock:public Tetromino{
        char type;
    public:
        TBlock(int speed, int value);
        Info getInfo() const override; //allows retrieval of type
        ~TBlock() override;
};
