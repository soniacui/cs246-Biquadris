#include "tetromino.h"
#include "info.h"
#include <memory>
#include <vector>

using namespace std;

void Tetromino::notify(Subject &notifier) {
    BoardInfo *bInfo = notifier.getInfo(); //all its observers' getInfo() return type BoardInfo
    if (bInfo->deletedRow != -1) { //case that the board had deleted a row, must update absCoords
        //blah blah stuff goes here will do later, i need to cook
    }
    else //case that board is notifying opponent or displays (nothing to delete)
        return;
}

Info *Tetromino::getInfo() const {
    unique_ptr<TetrominoInfo> tInfo{ new TetrominoInfo(previously, absCoords, type, value, isDeleted) };
    return tInfo;
}