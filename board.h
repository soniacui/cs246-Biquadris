#ifndef _BOARD_
#define _BOARD_
#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>

class Tetromino;
class LevelData;

class Board:public Subject, public Observer {
        const int HEIGHT = 15;
        const int WIDTH = 11;
	    static int highScore = 0; //default set highscore to 0
        vector<vector<char>> grid;
    	string currPunish;
        Observer *display;
        Tetromino *currTetro;
        unique_ptr<Tetromino> nextTetro;
        vector<Tetromino *> tetrominoes;
        bool isBlind;
        bool isTurn;
        bool menu;
        string path;
        int seed;
	    int sinceLastClear;
	    int difficulty;
	    int playerID;
	    int score;
        int deletedRow;
	    LevelData tetroFactory;
        void deleteTetro(Tetromino *destroy);
    public:
	    Board(int difficulty, int playerID, Observer *display, string path = "", int seed = -1);
	    void notify(Subject &notifier) override; //once notified, react as appropriate based on caller, would always call getInfo(), relay state change with notifyObservers()
	    Info *getInfo() const override; //creates and returns a BoardInfo pointer
	    bool checkDropped(TetrominoInfo tetroInfo) const;  //checks to see if tetromino move signals end of turn
	    void clearLine(); //contains all end of turn effects, resets tetroFactory and currPunish to clean state, additional call to notifyObservers() for each removal
        void toggleRandom(string newPath = "");
	    bool isGameOver();
	    void restart();
        void performAction(string action, string path = "");
	    void sufferPunishment(string effect); //augments tetroFactory/grid to accomodate effect
	    void generateTetromino(); //create next tetronimo to be dropped, add to tetrominoes
};

#endif
