#include "tetromino.h"
#include "info.h"
#include <memory>
#include <vector>
#include <iostream> //////asdsadasdsadasdasREMOVE

using namespace std;

char Tetromino::getType() {
    return type;
}

void Tetromino::updateGrid(vector<vector<char>> grid) {
    currGrid = grid;
}

Tetromino::Tetromino(vector<vector<char>> currGrid, int difficulty, char type) : currGrid{ currGrid }, value { difficulty }, type{ type } {
    if (difficulty == 3 || difficulty == 4) {
        speed = 1;
    }
    else {
        speed = 0;
    }
    isDeleted = false;
    isDropped = false;
    isHeavy = false;
    previously = vector<vector<int>>(4, vector<int>(2, -1));
}

IBlock::IBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {0, 13}, {0, 12}, {0, 11} };
}
IBlock::~IBlock() {}

JBlock::JBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {0, 13}, {0, 12}, {1, 14} };
}
JBlock::~JBlock() {}

LBlock::LBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 13}, {1, 13}, {2, 13}, {2, 14} };
}
LBlock::~LBlock() {}

OBlock::OBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {0, 13}, {1, 14}, {1, 13} };
}
OBlock::~OBlock() {}

SBlock::SBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 13}, {1, 13}, {1, 14}, {2, 14} };
}
SBlock::~SBlock() {}

ZBlock::ZBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {1, 14}, {1, 13}, {2, 13} };
}
ZBlock::~ZBlock() {}

TBlock::TBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {1, 14}, {2, 14}, {1, 13} };
}
TBlock::~TBlock() {}

StarBlock::StarBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {5, 14} };
}
StarBlock::~StarBlock() {}

void Tetromino::notify(Subject &notifier) {
    shared_ptr<BoardInfo> bInfo = notifier.getInfo(); //all its observers' getInfo() return type BoardInfo
    cout << "looping" << endl;
    if (bInfo->deletedRow != -1) { //case that the board had deleted a row, must update absCoords
        if (isDeleted) //if already deleted, no new points awarded
            return;
        for (int i = 0; i < absCoords.size(); i++) {
            if (absCoords[i][1] == bInfo->deletedRow) { //remove block's coordinates that have been deleted
                absCoords.erase(absCoords.begin() + i);
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

shared_ptr<TetrominoInfo> Tetromino::getTetroInfo() {
    shared_ptr<TetrominoInfo> tInfo{ new TetrominoInfo(previously, absCoords, type, value, speed, isDropped, isDeleted, isHeavy) };
    cout << "ASDASDASDAS" << tInfo->absCoords[0][0] << endl;
    return tInfo;
}

shared_ptr<BoardInfo> Subject::getInfo() const { return nullptr; }

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
	if (bottom_max > 1) {
	      cout << "CAN STILL MOVE DOWN" << endl;	
		// if "down" is a valid move, shift all y coords 1 down
		for (int i = 0; i < absCoords.size(); ++i) {
			absCoords[i][1] = absCoords[i][1] - 1;
		}	

	}

}

//notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
void Tetromino::move(string direction) { // move left/right
	cout << "b.5555555555" << endl;
	updatePreviously();
	cout << "cccccccc" << previously.size() << endl;
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
            vector <int> temp2 = { absCoords[i][1], -(absCoords[i][0]) };
			temp.emplace_back(temp2); // (y, -x)
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











