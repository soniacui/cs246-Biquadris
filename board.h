#ifndef _BOARD_
#define _BOARD_
#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>

class TetrominoInfo;
class Tetromino;
class LevelData;

class Board:public Subject, public Observer {
        const int HEIGHT = 15;
        const int WIDTH = 11;
	static int highScore; //default set highscore to 0 in .cc
	std::vector<std::vector<char>> grid;
	std::string currPunish;
        Observer *display;
        Tetromino *currTetro;
	std::unique_ptr<Tetromino> nextTetro;
	std::vector<Tetromino *> tetrominoes;
        bool isBlind;
        bool isTurn;
        bool menu;
	std::string path;
        int seed;
	    int sinceLastClear;
	    int difficulty;
	    int playerID;
	    int score;
        int deletedRow;
	    LevelData tetroFactory;
        void deleteTetro(Tetromino *destroy);
    public:
	    Board(int difficulty, int playerID, Observer *display, std::string path = "", int seed = -1);
	    void notify(Subject &notifier) override; //once notified, react as appropriate based on caller, would always call getInfo(), relay state change with notifyObservers()
	    Info *getInfo() const override; //creates and returns a BoardInfo pointer
	    bool checkDropped(TetrominoInfo tetroInfo) const;  //checks to see if tetromino move signals end of turn
	    void clearLine(); //contains all end of turn effects, resets tetroFactory and currPunish to clean state, additional call to notifyObservers() for each removal
        void toggleRandom(std::string newPath = "");
	    bool isGameOver();
	    void restart();
        void performAction(std::string action, std::string path = "");
	    void sufferPunishment(std::string effect); //augments tetroFactory/grid to accomodate effect
	    void generateTetromino(); //create next tetronimo to be dropped, add to tetrominoes
};

#endif
