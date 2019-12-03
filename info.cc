#include "info.h"
#include <vector>

class Tetromino;

using namespace std;

Info::Info(string infoType) : infoType{ infoType } {}
Info::~Info() {}

BoardInfo::BoardInfo(vector<vector<char>> &grid, string punishType, int difficulty, int score, int playerID, int deletedRow, Tetromino *nextTetro, bool isTurn, bool menu, bool hasLost, string infoType): 
    Info(infoType), grid{ grid }, deletedRow{ deletedRow }, isTurn{ isTurn }, difficulty{ difficulty }, score{ score }, playerID{ playerID }, nextTetro{nextTetro}, menu{ menu }, hasLost{ hasLost }, punishType{ punishType } {}
BoardInfo::~BoardInfo() {}

TetrominoInfo::TetrominoInfo(vector<vector<int>> &previously, vector<vector<int>> &absCoords, char type, int value, int speed, bool isDropped, bool isDeleted, bool isHeavy):
    Info(), previously{ previously }, absCoords{ absCoords }, type{ type }, isDeleted{ isDeleted }, isDropped{ isDropped }, isHeavy{ isHeavy }, value{ value }, speed{ speed } {}
TetrominoInfo::~TetrominoInfo() {}
