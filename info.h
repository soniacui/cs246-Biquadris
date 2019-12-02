#ifndef _INFO_
#define _INFO_
#include <vector>

struct Info{
	std::string infoType;
	Info(std::string infoType = "tetromino"); //default constructs to information about a tetromino
	virtual ~Info() = 0;
};

struct BoardInfo:public Info{
	std::vector<std::vector<char>> grid;
	std::string punishType;
    int playerID;
    int deletedRow;
    int difficulty;
    int score;
    Tetromino *nextTetro;
    bool isTurn;
    bool menu;
    bool hasLost;
	BoardInfo(std::vector<std::vector<char>> &grid, std::string punishType, int playerID, int deletedRow, Tetromino *nextTetro, bool isTurn, bool menu, bool hasLost, std::string infoType); //specify that infoType is board
    ~BoardInfo() override;
};

struct TetrominoInfo:public Info{
	std::vector<std::vector<int>> previously;
	std::vector<std::vector<int>> absCoords;
	char type;
	bool isDeleted;
    bool isDropped;
    bool isHeavy;
	int value;
	TetrominoInfo(std::vector<std::vector<int>> &previously, std::vector<std::vector<int>> &absCoords, char type, int value, bool isDeleted, bool isDropped);
    ~TetrominoInfo() override;
};

#endif
