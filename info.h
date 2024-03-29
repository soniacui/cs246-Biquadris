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
	BoardInfo(vector<vector<char>> &grid, string punishType, string infoType); //specify that infoType is board
};

struct TetrominoInfo:public Info{
	vector<vector<int>> absCoords;
	char type;
	bool isDeleted;
	int value;
	TetrominoInfo(vector<vector<int>> &absCoords, char type, int value, bool isDeleted = false); //generally, tetromino does not notify it has just been deleted, default false
};

#endif
