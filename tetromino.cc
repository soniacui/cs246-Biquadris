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

//notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
void Tetromino::move(string direction) { // move left/right

	// update previously
	for (int i = 0; i < absCoords.size(); ++i) {
		previously[i][0] = absCoords[i][0];
		previously[i][1] = absCoords[i][1];
	}

	if (direction == "right") {

		// find right-most pixel 
		int right_max = 0;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][0] > right_max) {
				right_max = absCoords[i][0];
			}
		}

		// check if the block can move right
		if (right_max < currGrid[0].size() - 1) {  // ** i'm P SURE it's supposed to be -1
			// if "right" is a valid move, shift all x coords 1 right
			for (int i = 0; i < absCoords.size(); ++i) {
				absCoords[i][0] = absCoords[i][0] + 1;
			}

		}


	} else if (direction == "left") { 

		// find left-most pixel 
		int left_max = currGrid[0].size() - 1;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][0] < left_max) {
				left_max = absCoords[i][0];
			}
		}

		// check if the block can move left
		if (left_max > 0) { 
			// if "left" is a valid move, shift all x coords 1 left
			for (int i = 0; i < absCoords.size(); ++i) {
				absCoords[i][0] = absCoords[i][0] - 1;
			}

		}


	} else if (direction == "down") {  // dropping to bottom most row or into another block does not end turn

		// find bottom-most pixel 
		int bottom_max = 0;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][1] > bottom_max) {
				bottom_max = absCoords[i][1];
			}
		}

		// check if the block can move down
		if (bottom_max > 0) { 
			// if "down" is a valid move, shift all y coords 1 down
			for (int i = 0; i < absCoords.size(); ++i) {
				absCoords[i][1] = absCoords[i][0] - 1;
			}	

		}


	}

	notifyObservers();  // notify observers

}

void Tetromino::rotate(string direction) {

	// update previously
	for (int i = 0; i < absCoords.size(); ++i) {
		previously[i][0] = absCoords[i][0];
		previously[i][1] = absCoords[i][1];
	}

	if (direction == "clockwise") {
		//update abscoords
		
		//find bottom-left corner
		//check if valid move
		//some rotating algorithm

	} else if (direction == "counterclockwise") {
		//update previously
		//update abscoords

	}

	notifyObservers();
}


void Tetromino::drop() {   // A TURN IS NOT OVER UNTIL THE BLOCK HAS BEEN DROPPED OR THE BLOCK HAS BEEN 'HEAVYED' TO THE BOTTOM-MOST POSSIBLE

	// update previously
	for (int i = 0; i < absCoords.size(); ++i) {
		previously[i][0] = absCoords[i][0];
		previously[i][1] = absCoords[i][1];
	}

	//update abscoords (check against currgrid's highest tile)
	//shift all tetro's coords 1 down until at lowest possible

	//find current block's left most pixel
	int left_max = currGrid[0].size() - 1;
	for (int i = 0; i < absCoords.size(); ++i) {
		if (absCoords[i][0] < left_max) {
			left_max = absCoords[i][0];
		}
	}

	//find current block's right most pixel
	int right_max = 0;
	for (int i = 0; i < absCoords.size(); ++i) {
		if (absCoords[i][0] > right_max) {
			right_max = absCoords[i][0];
		}
	}

	// find bottom-most pixel that is under current block 
	int bottom_max = 0;
	for (int i = 0; i < currGrid.size(); ++i) {  // rows of currGrid
		for (int j = left_max; j <= right_max; ++j) {  // cols of current block
			if (currGrid[i][j] != ' ') {
				bottom_max = i;
			}
		
		}
	}

	// shift block as down as possible
	for (int i = 0; i < absCoords.size(); ++i) {
		absCoords[i][1] = currGrid.size() - absCoords[i][0] + bottom_max;
	}	

	notifyObservers();
}


