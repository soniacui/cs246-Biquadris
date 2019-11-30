#include "info.h"
#include <vector>

class Tetromino;

using namespace std;

Info::Info(string infoType) : infoType{ infoType } {}
Info::~Info() {}

BoardInfo::BoardInfo(vector<vector<char>> &grid, string punishType, int deletedRow, Tetromino *nextTetro, bool isTurn, bool menu, bool hasLost, string infoType): 
    Info(infoType), grid{ grid }, deletedRow{ deletedRow }, isTurn{ isTurn }, menu{ menu }, hasLost{ hasLost }, punishType{ punishType } {}
BoardInfo::~BoardInfo() {}

TetrominoInfo::TetrominoInfo(vector<vector<int>> &previously, vector<vector<int>> &absCoords, char type, int value, bool isDropped, bool isDeleted, bool isHeavy):
    Info(), previously{ previously }, absCoords{ absCoords }, type{ type }, isDeleted{ isDeleted }, isDrpped{ isDropped }, isHeavy{ isHeavy }, value{ value } {}
TetrominoInfo::~TetrominoInfo() {}