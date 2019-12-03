#ifndef _TETROMINO_
#define _TETROMINO_
#include "observer.h"
#include "subject.h"
#include <vector>

class Tetromino:public Subject, public Observer{
    protected:
	    int speed;
	    int value;
	    char type;
	    bool isDeleted;
        bool isDropped;
		bool isHeavy;
		std::vector<std::vector<int>> previously; //remembers last position for grid to clear
		std::vector<std::vector<int>> absCoords;
		std::vector<std::vector<char>> currGrid;
    public:
	    Tetromino(std::vector<std::vector<char>> currGrid, int difficulty, char type);
	    void move(std::string direction);
	    void rotate(std::string direction); //notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
	    void drop();
        void increaseSpeed(int increase);
	std::shared_ptr<TetrominoInfo> getTetroInfo() override;
	    void notify(Subject &notifier) override; //cares only about when toDelete is not empty
	    virtual ~Tetromino() = 0; //default destructor, also make Tetromino abstract
	    void toggleHeavy();
	    void updatePreviously();
	    void moveDown();
        void updateGrid(std::vector<std::vector<char>> grid);
        char getType();
};

class IBlock:public Tetromino{
    public:
        IBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'I');
	    ~IBlock() override;
};

class JBlock:public Tetromino{
    public:
        JBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'J');
        ~JBlock() override;
};

class LBlock:public Tetromino{
    public:
        LBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'L');
        ~LBlock() override;
};

class OBlock:public Tetromino{
    public:
        OBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'O');
        ~OBlock() override;
};

class SBlock:public Tetromino{
    public:
        SBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'S');
        ~SBlock() override;
};

class ZBlock:public Tetromino{
    public:
        ZBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'Z');
        ~ZBlock() override;
};

class TBlock:public Tetromino{
    public:
        TBlock(std::vector<std::vector<char>> grid, int difficulty, char type = 'T');
        ~TBlock() override;
};

class StarBlock:public Tetromino{
    public:
        StarBlock(std::vector<std::vector<char>> grid, int difficulty, char type = '*');
        ~StarBlock() override;
};

#endif
