#ifndef _INFO_
#define _INFO_
#include <vector>

struct Info{
	string infoType;
	Info(string infoType = "tetromino"); //default constructs to information about a tetromino
	virtual ~Info() = 0;
};

struct BoardInfo:public Info{
	vector<vector<char>> grid;
	string punishType;
    int deletedRow;
    int difficulty;
    int score;
    bool isTurn;
    bool menu;
    bool hasLost;
	BoardInfo(vector<vector<char>> &grid, string punishType, int deletedRow, bool isTurn, bool menu, bool hasLost, string infoType); //specify that infoType is board
    ~BoardInfo() override;
};

struct TetrominoInfo:public Info{
    vector<vector<int>> previously;
	vector<vector<int>> absCoords;
	char type;
	bool isDeleted;
    bool isDropped;
    bool isHeavy;
	int value;
	TetrominoInfo(vector<vector<int>> &previously, vector<vector<int>> &absCoords, char type, int value, bool isDeleted, bool isDropped);
    ~TetrominoInfo() override;
};

#endif
