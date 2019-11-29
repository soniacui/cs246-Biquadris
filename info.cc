#include "info.h"
#include <vector>

using namespace std;

Info::Info(string infoType) : infoType{ infoType } {}
Info::~Info() {}

BoardInfo::BoardInfo(vector<vector<char>> &grid, string punishType, int deletedRow, string infoType): 
    Info(infoType), grid{ grid }, deletedRow{ deletedRow }, punishType{ punishType } {}
BoardInfo::~BoardInfo() {}

TetrominoInfo::TetrominoInfo(vector<vector<int>> &previously, vector<vector<int>> &absCoords, char type, int value, bool isDropped, bool isDeleted, bool isHeavy):
    Info(), previously{ previously }, absCoords{ absCoords }, type{ type }, isDeleted{ isDeleted }, isDrpped{ isDropped }, isHeavy{ isHeavy }, value{ value } {}
TetrominoInfo::~TetrominoInfo() {}