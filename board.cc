#include "board.h"
#include "info.h"
#include <memory>
#include <vector>

using namespace std;

void Board::notify(Subject &notifier) {
    Info *info = notifier.getInfo(); //get relevant information from caller
    if (info->infoType == "tetromino") { //if caller is a tetromino
        if (info->isDeleted) { //case for tetromino has been removed from board
            score += (info->score + 1) * (info->score + 1); //add points
        }
        else { //handling tetromino representation on internal grid
            for (int i = 0; i < info->absCoords.size(); i++) {
                grid[info->previously[i][1]][info->previously[i][0]] = ' '; //fill old location
                grid[info->absCoords[i][1]][info->absCoords[i][0]] = info->type; //new location
            }
            if (checkDropped(*info)) //check if the tetromino has dropped to the bottom
                clearLine(); //complete end of turn actions, add points clear lines etc.
        }
    }
    else { //if caller is opponent board, only case is to suffer effect
        string effect = info->punishType;
        sufferPunishment(effect);
    }
    notifyObservers(); //relay message to observers, namely the displays
}

Info *Board::getInfo() const {
    unique_ptr<BoardInfo> bInfo { new BoardInfo(grid, currPunish, deletedRow, "board") };
    return bInfo;
}