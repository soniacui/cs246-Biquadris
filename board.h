#ifndef _BOARD_
#define _BOARD_
#include <vector>

class Subject;
class Tetromino;
class LevelData;

class Board:public Subject, public Observer{
	static int highScore;
	vector<vector<char>> grid;
	vector<Tetromino*> tetrominoes;
	Window *windowPtr;
	Console *consolePtr;
	vector<vector<int>> toDelete;
	string currPunish;
	string path;
	int sinceLastClear;
	int difficulty;
	int playerID;
	int score;
	LevelData tetroFactory;
    public:
	Board(int difficulty, int playerID, Window *windowPtr, Console *consolePtr, string path = "");
	void notify(Subject &notifier) override; //once notified, react as appropriate based on caller, would always call getInfo(), relay state change with notifyObservers()
	Info getInfo() const override; //creates and returns a BoardInfo
	bool checkDropped(TetrominoInfo tetroInfo) const;  //checks to see if tetromino move signals end of turn
	void clearLine(); //contains all end of turn effects, resets tetroFactory and currPunish to clean state, additional call to notifyObservers() for each removal
	
	bool isGameOver();
	void restart();
	// NOTE the blind effect may be difficult to implement

	void sufferPunishment(string effect); //augments tetroFactory/grid to accomodate effect
	void choosePunishment(); //prompt user to choose effect for opponent
	Tetromino *generateTetromino(); //create next tetronimo to be dropped, add to tetrominoes
	~Board();
};

#endif
