#include "tetromino.h"
#include "info.h"
#include <memory>
#include <vector>

using namespace std;

void Tetromino::notify(Subject &notifier) {
    BoardInfo *bInfo = notifier.getInfo(); //all its observers' getInfo() return type BoardInfo
    if (bInfo->deletedRow != -1) { //case that the board had deleted a row, must update absCoords
        if (isDeleted) //if already deleted, no new points awarded
            return;
        for (int i = 0; i < absCoords.size(); i++) {
            if (absCoords[i][1] == bInfo->deletedRow) { //remove block's coordinates that have been deleted
                absCoords.erase(i);
                i--;
            }
            else if (absCoords[i][1] > bInfo->deletedRow) { //shift block's coordinates above the deleted line down
                absCoords[i][1]--;
            }
        }
        if (absCoords.size() == 0) { //if there is nothing left, it has been deleted
            isDeleted = true;
            notifyObservers(); //notify board to give extra points
        }
    }
    else //case that board is notifying opponent or displays (nothing to delete)
        return;
}

Info *Tetromino::getInfo() const {
    bool heavy = false;
    if (speed > 0)
        heavy = true;
    unique_ptr<TetrominoInfo> tInfo{ new TetrominoInfo(previously, absCoords, type, value, isDeleted, isDropped, heavy) };
    return tInfo;
}