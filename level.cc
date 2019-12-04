#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "tetromino.h"
#include "level.h"

using namespace std;

LevelData::LevelData(int difficulty, int playerID, string path, int seed): difficulty{difficulty}, playerID{playerID}, path{path}, seed{seed} {
	index = 0; 
	string s;
        ifstream input;
	if (path != "") {          // if any sequence was given  
            input.open(path, std::ifstream::in);        
            while (input >> s) { 
		seq.push_back(s);  //load input seq  
	    }
	} else if (difficulty == 0) { // if no sequence is given and level is 0, use default files
		if (playerID == 1) {
	    		input.open("sequence1.txt", std::ifstream::in);

		} else if (playerID == 2) {
	    		input.open("sequence2.txt", std::ifstream::in);
		}
	    	while (input >> s) {
			seq.push_back(s);
	 	}
	}
        if (seed != -1) {
	    srand(seed);
	}
}

Tetromino* LevelData::generateTetromino(vector<vector<char>> grid) {

    //generate normally
    //norandom/random (gives blocks)
    //seed
    
    int n = -1; 
    string s;
    Tetromino *t;
    if (difficulty == 0 || path != "") { // if user has called norandom with a file path
	if (index >= seq.size()) {
		index = 0; // if we reached the end of our seq file, go back to top
	}
	s = seq.at(index); 
	++index;

	if (s == "S") {
		t = new SBlock(grid, difficulty);
	} else if (s == "Z") {
		t = new ZBlock(grid, difficulty);
	} else if (s == "I") {
		t = new IBlock(grid, difficulty);
	} else if (s == "O") {
		t = new OBlock(grid, difficulty);
	} else if (s == "J") {
		t = new JBlock(grid, difficulty);
	} else if (s == "L") {
		t = new LBlock(grid, difficulty);
	} else if (s == "T") {
		t = new TBlock(grid, difficulty);
	}
	return t;
    }
    if (seed != -1) {  // if user has supplied a seed
	n = abs(rand()) % 7;        
    } 
    if (difficulty == 1) {
	if (n != -1) { // check if seed has been supplied
		n = abs(rand()) % 12; 
	}
	if (n == 0) {
		t = new SBlock(grid, difficulty);
	} else if (n == 1) {
		t = new ZBlock(grid, difficulty);
	} else if (n == 2 || n == 3) {
		t = new IBlock(grid, difficulty);
	} else if (n == 4 || n == 5) {
		t = new OBlock(grid, difficulty);
        } else if (n == 6 || n == 7) {
		t = new JBlock(grid, difficulty);
	} else if (n == 8 || n == 9) {
		t = new LBlock(grid, difficulty);
	} else {
		t = new TBlock(grid, difficulty);
	}  
     } else if (difficulty == 2) {
	if (n != -1) {  // check if seed has been supplied
		n = abs(rand()) % 7;
	}
	if (n == 0) {
		t = new SBlock(grid, difficulty);
	} else if (n == 1) {
		t = new ZBlock(grid, difficulty);
	} else if (n == 2) {
		t = new IBlock(grid, difficulty);
	} else if (n == 3) {
		t = new OBlock(grid, difficulty);
	} else if (n == 4) {
		t = new JBlock(grid, difficulty);
	} else if (n == 5) {
		t = new LBlock(grid, difficulty);
	} else {
		t = new TBlock(grid, difficulty);
	}  
     } else if (difficulty == 3 || difficulty == 4) { // level 3 or 4
	if (n != -1) {  // check if seed has been supplied
		n = abs(rand()) % 9;
	}
	if (n == 0 || n == 1) {
		t = new SBlock(grid, difficulty);
	} else if (n == 2 || n == 3) {
		t = new ZBlock(grid, difficulty);
	} else if (n == 4) {
		t = new IBlock(grid, difficulty);
	} else if (n == 5) {
		t = new OBlock(grid, difficulty);
	} else if (n == 6) {
		t = new JBlock(grid, difficulty);
	} else if (n == 7) {
		t = new LBlock(grid, difficulty);
	} else {
		t = new TBlock(grid, difficulty);
	}  
    }
    return t;
}


//returns a tetromino pointer of the desired type{L, J, O ... *}
Tetromino* LevelData::forceGenerate(vector<vector<char>> grid, std::string typeForced) {
	Tetromino *t;
	if (typeForced == "S") {
		t = new SBlock(grid, difficulty);
	} else if (typeForced == "Z") {
		t = new ZBlock(grid, difficulty);
	} else if (typeForced == "I") {
		t = new IBlock(grid, difficulty);
	} else if (typeForced == "O") {
		t = new OBlock(grid, difficulty);
	} else if (typeForced == "J") {
		t = new JBlock(grid, difficulty);
	} else if (typeForced == "L") {
		t = new LBlock(grid, difficulty);
	} else {
		t = new TBlock(grid, difficulty);
	}  
	return t;
}

