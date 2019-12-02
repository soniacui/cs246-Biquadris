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

unique_ptr<TetrominoInfo> Tetromino::getInfo() const {
    unique_ptr<TetrominoInfo> tInfo{ new TetrominoInfo(previously, absCoords, type, value, isDeleted) };
    return tInfo;
}


// ***************isHeavy needs to be given a default value in the ctor
void Tetromino::toggleHeavy() {
	isHeavy = !(isHeavy);
}


// update previously
void Tetromino::updatePreviously() { // *********** add to .h and uml
	for (int i = 0; i < absCoords.size(); ++i) {
		previously[i][0] = absCoords[i][0];
		previously[i][1] = absCoords[i][1];
	}
}


// moves a Tetromino piece 1 down // *************** add to .h and uml
void Tetromino::moveDown() {
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

//notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
void Tetromino::move(string direction) { // move left/right

	updatePreviously();

	if (direction == "right") {

		// find right-most pixel 
		int right_max = 0;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][0] > right_max) {
				right_max = absCoords[i][0];
			}
		}

		// check if the block can move right
		if (right_max < currGrid[0].size() - 1) { 
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


	} else if (direction == "down") {  // down-ing to bottom most row or into another block does not end turn	
		moveDown();
	}

	int spaces = speed;
	if (isHeavy) {
		spaces = spaces + 2;
	}
	for (int i = 0; i < spaces; ++i) {
		moveDown();
	}
	notifyObservers();

}

void Tetromino::rotate(string direction) {

	updatePreviously();

	if (direction == "clockwise") {

		//check if valid move ******************

		// find left-most pixel 
		int left_max = currGrid[0].size() - 1;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][0] < left_max) {
				left_max = absCoords[i][0];
			}
		}

		// find bottom-most pixel 
		int bottom_max = currGrid.size() - 1;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][1] < bottom_max) {
				bottom_max = absCoords[i][1];
			}
		}
		//bottom-left-most = (left-most, bottom-most)
		

		vector<vector<int>> temp;
		for (int i = 0; i < absCoords.size(); ++i) {
			absCoords[i][0] = absCoords[i][0] - left_max; //shift x to origin
			absCoords[i][1] = absCoords[i][1] - bottom_max; //shift y to origin
			temp.emplace_back({absCoords[i][1], -(absCoords[i][0])}); // (y, -x)
		}
		absCoords = temp; // rotate	

		// find NEW left-most pixel 
		int new_left_max = currGrid[0].size() - 1;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][0] < left_max) {
				left_max = absCoords[i][0];
			}
		}

		// find NEW bottom-most pixel 
		int new_bottom_max = currGrid.size() - 1;
		for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][1] < bottom_max) {
				bottom_max = absCoords[i][1];
			}
		}

		//shift back
		for (int i = 0; i < absCoords.size(); ++i) {
			absCoords[i][0] = absCoords[i][0] + (left_max - new_bottom_max);  // abs????*********
			absCoords[i][1] = absCoords[i][1] + (bottom_max - new_bottom_max);
		}

	} else if (direction == "counterclockwise") {
		//update previously
		//update abscoords

	}

	for (int i = 0; i < speed; ++i) {
		moveDown();
	}

	notifyObservers();
}


void Tetromino::drop() {  

	updatePreviously();

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
	int bottom_max = currGrid.size() - 1;;
	for (int i = 0; i < currGrid.size(); ++i) {  // rows of currGrid
		for (int j = left_max; j <= right_max; ++j) {  // cols of current block
			if (currGrid[i][j] != ' ') {
				bottom_max = i;
			}
		
		}
	}

	// shift block as down as possible
	for (int i = 0; i < absCoords.size(); ++i) {
		absCoords[i][1] = currGrid.size() - absCoords[i][1] + bottom_max;
	}	

	notifyObservers();
}

Tetromino::~Tetromino() {}











