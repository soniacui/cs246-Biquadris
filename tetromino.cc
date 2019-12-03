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
    absCoords = { {0, 14}, {1, 14}, {2, 14}, {3, 14} };
}
IBlock::~IBlock() {}

JBlock::JBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 15}, {0, 14}, {1, 14}, {2, 14} };
}
JBlock::~JBlock() {}

LBlock::LBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {1, 14}, {2, 14}, {2, 15} };
}
LBlock::~LBlock() {}

OBlock::OBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {1, 14}, {0, 15}, {1, 15} };
}
OBlock::~OBlock() {}

SBlock::SBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 14}, {1, 14}, {1, 15}, {2, 15} };
}
SBlock::~SBlock() {}

ZBlock::ZBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 15}, {1, 15}, {1, 14}, {2, 14} };
}
ZBlock::~ZBlock() {}

TBlock::TBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {0, 15}, {1, 15}, {2, 15}, {1, 14} };
}
TBlock::~TBlock() {}

StarBlock::StarBlock(vector<vector<char>> grid, int difficulty, char type) : Tetromino(grid, difficulty, type) {
    absCoords = { {5, 14} };
}
StarBlock::~StarBlock() {}

void Tetromino::notify(Subject &notifier) {
	if (popped)
		return;
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

void Tetromino::toggleHeavy() {
	isHeavy = !(isHeavy);
}


// update previously
void Tetromino::updatePreviously() {
	for (int i = 0; i < absCoords.size(); ++i) {
		previously[i][0] = absCoords[i][0];
		previously[i][1] = absCoords[i][1];
	}
}

int Tetromino::findLeftMost() {
	// find left-most pixel 
	int left_max = currGrid[0].size() - 1;
	for (int i = 0; i < absCoords.size(); ++i) {
		if (absCoords[i][0] < left_max) {
			left_max = absCoords[i][0];
		}
	}
	return left_max;
}

int Tetromino::findRightMost() {
	// find right-most pixel 
	int right_max = 0;
	for (int i = 0; i < absCoords.size(); ++i) {
			if (absCoords[i][0] > right_max) {
			right_max = absCoords[i][0];
		}
	}
	return right_max;
}

int Tetromino::findBottomMost() {
	// find bottom-most pixel 
	int bottom_max = currGrid.size() - 1;
	for (int i = 0; i < absCoords.size(); ++i) {
		if (absCoords[i][1] < bottom_max) {
			bottom_max = absCoords[i][1];
		}
	}
	return bottom_max;
}


// moves a Tetromino piece 1 down 
void Tetromino::moveDown() {

	int bottom_most = findBottomMost();

	if (bottom_most > 0) {
		for (int i = 0; i < absCoords.size(); ++i) {
			for (int j = 0; j < absCoords.size(); ++j) {
				if ((currGrid[absCoords[i][0]][absCoords[i][1] - 1] != currGrid[absCoords[j][0]][absCoords[j][1]]) &&  //not valid case
				    (currGrid[absCoords[i][0]][absCoords[i][1] - 1] != ' ')) {
						return;
					}	
			}
		}
		// if "bottom" is a valid move, shift all y coords 1 down
		cout << "trying to move down. printing shifted coords: " << endl;
		for (int i = 0; i < absCoords.size(); ++i) {
			absCoords[i][1] = absCoords[i][1] - 1;
			cout << absCoords[i][0] << ", " << absCoords[i][1] << endl;
		}
	}
}

// dir = 1 moves 1 right, dir = -1 moves 1 left
void Tetromino::moveLeftRight(int dir) {

	// for each shifted abscoords, if it collides with a non-abscoords grid pixel, or is outside of bounds, don't move it. otherwise, move it
	for (int i = 0; i < absCoords.size(); ++i) {
			for (int j = 0; j < absCoords.size(); ++j) {
				if ((currGrid[absCoords[i][0] + dir][absCoords[i][1]] != currGrid[absCoords[j][0]][absCoords[j][1]]) &&
				    (currGrid[absCoords[i][0] + dir][absCoords[i][1]] != ' ')) {
						return;
					}	
			}
		}
		// if "right" is a valid move, shift all x coords 1 right	
		cout << "trying to move left/right. printing shifted coords: " << endl;
		for (int i = 0; i < absCoords.size(); ++i) {
			absCoords[i][0] = absCoords[i][0] + dir;
			cout << absCoords[i][0] << ", " << absCoords[i][1] << endl;
	}

}

//notifyObservers called upon every state change (includes move, rotate, drop, and instances of notify)
void Tetromino::move(string direction) { // move left/right
	cout << "b.5555555555" << endl;
	updatePreviously();
	cout << "cccccccc" << previously.size() << endl;

	if (direction == "right") {
		int right_most = findRightMost();
		if (right_most < currGrid[0].size() - 1) {
			moveLeftRight(1);
		}
	} else if (direction == "left") {
		int left_most = findLeftMost();
		if (left_most > 0) {
			moveLeftRight(-1);
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

		vector<vector<int>> check = absCoords; // a "trial" vector to see if the rotate is valid
		int left_most = findLeftMost();        //find left most before shifting
                int bottom_most = findBottomMost();     //find bottom most before shifting

		// shift trial vector to origin, and rotate clockwise
		for (int i = 0; i < check.size(); ++i) {
			check.emplace_back(vector<int>{absCoords[i][1] - bottom_most, -(absCoords[i][0] - left_most)});
		}

		// find right-most pixel after rotating
		int new_left_most = currGrid[0].size() - 1;
		for (int i = 0; i < check.size(); ++i) {
			if (check[i][0] > new_left_most) {
				new_left_most = check[i][0];
			}
		}
		// find bottom-most pixel after rotating
		int new_bottom_most = currGrid.size() - 1;
		for (int i = 0; i < check.size(); ++i) {
			if (check[i][1] < new_bottom_most ) {
				new_bottom_most = check[i][1];
			}
		}
	
		//shift back to desired location and check if valid move
		for (int i = 0; i < check.size(); ++i) {
			check[i][0] = check[i][0] + abs(left_most - new_left_most); 
			check[i][1] = check[i][1] + abs(bottom_most - new_bottom_most);
			if ((check[i][0] < 0) && (check[i][0] > currGrid[0].size() - 1) &&     //x is out of bounds
			    (check[i][1] > currGrid.size() - 1) && (check[i][1] < 0) &&       //y is out of bounds
			    (currGrid[check[i][0]][check[i][1]] != ' ')) {                  //rotated block overlaps
				return;     //if move is not valid, exit
			}
		}
		absCoords = check; //if move was valid, copy the 'check' vector

	} else if (direction == "counterclockwise") {
		vector<vector<int>> check = absCoords; // a "trial" vector to see if the rotate is valid
                int left_most = findLeftMost();        //find left most before shifting
                int bottom_most = findBottomMost();     //find bottom most before shifting
		// shift trial vector to origin, and rotate clockwise
		for (int i = 0; i < check.size(); ++i) {
			check.emplace_back(vector<int>{-(absCoords[i][1] - bottom_most), absCoords[i][0] - left_most}); 
		}


		// find right-most pixel after rotatingi
		int new_left_most = currGrid[0].size() - 1;
		for (int i = 0; i < check.size(); ++i) {
			if (check[i][0] > new_left_most) {
				new_left_most = check[i][0];
			}
		}
		// find bottom-most pixel after rotating
		int new_bottom_most = currGrid.size() - 1;
		for (int i = 0; i < check.size(); ++i) {
			if (check[i][1] < new_bottom_most ) {
				new_bottom_most = check[i][1];
			}
		}
	
		//shift back to desired location and check if valid move
		for (int i = 0; i < check.size(); ++i) {
			check[i][0] = check[i][0] + abs(left_most - new_left_most); 
			check[i][1] = check[i][1] + abs(bottom_most - new_bottom_most);
			if ((check[i][0] < 0) && (check[i][0] > currGrid[0].size() - 1) &&     //x is out of bounds
			    (check[i][1] > currGrid.size() - 1) && (check[i][1] < 0) &&       //y is out of bounds
			    (currGrid[check[i][0]][check[i][1]] != ' ')) {                  //rotated block overlaps
				return;     //if move is not valid, exit
			}
		}
		absCoords = check; //if move was valid, copy the 'check' vector
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
	
	int left_most = findLeftMost();
	int right_most = findRightMost();

	// find bottom-most pixel that is under current block 
	int smallest_diff = currGrid.size();
	int diff = 0;
        bool start_count;
	for (int i = left_most; i <= right_most; ++i) { // cols of current block
		diff = 0;
		start_count = false;
		for (int j = currGrid.size() - 2; j >= 0; --j) { // rows of currGrid
			if ((currGrid[i][j] == ' ') && (currGrid[i][j + 1] != ' ')) {
				start_count = true;
			}
			if (start_count && (currGrid[i][j] == ' ')) {
				++diff;
			}
			if (start_count && (currGrid[i][j] != ' ')) {
				break;
			}
		}
		if (diff < smallest_diff) {
			smallest_diff = diff;
		}
	}

	// shift block as down as possible
	for (int i = 0; i < absCoords.size(); ++i) {
		absCoords[i][1] = absCoords[i][1] - smallest_diff;
	}
	
	isDropped = true;
	notifyObservers(); 
}

Tetromino::~Tetromino() {}











