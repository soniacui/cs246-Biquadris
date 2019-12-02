#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "tetromino.h"
#include "level.h"

using namespace std;

LevelData::LevelData(int difficulty, string path, int seed): difficulty{difficulty}, path{path}, seed{seed} {
	index = 0;
	string s;
	if (path != "") {             //load input seq  
            ifstream input (path, std::ifstream::in);        
            while (input >> s) {
		seq.push_back(s);
	    }
	}
        if (seed != -1) {
	    srand(seed);
	}
}

Tetromino* LevelData::generateTetromino() {

    //generate normally
    //norandom/random (gives blocks)
    //seed
    
    int n = -1; 
    string s;
    Tetromino *t;
    if (difficulty == 0 || path != "") { // if user has called norandom with a file path
	if (index > seq.size()) {
		index = 0; // if we reached the end of our seq file, go back to top
	
	} 
	s = seq.at(index);  
	++index;

	if (s == "S") {
		t = new SBlock(difficulty);
	} else if (s == "Z") {
		t = new ZBlock(difficulty);
	} else if (s == "I") {
		t = new IBlock(difficulty);
	} else if (s == "O") {
		t = new OBlock(difficulty);
	} else if (s == "J") {
		t = new JBlock(difficulty);
	} else if (s == "L") {
		t = new LBlock(difficulty);
	} else if (s == "T") {
		t = new TBlock(difficulty);
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
		t = new SBlock(difficulty);
	} else if (n == 1) {
		t = new ZBlock(difficulty);
	} else if (n == 2 || n == 3) {
		t = new IBlock(difficulty);
	} else if (n == 4 || n == 5) {
		t = new OBlock(difficulty);
        } else if (n == 6 || n == 7) {
		t = new JBlock(difficulty);
	} else if (n == 8 || n == 9) {
		t = new LBlock(difficulty);
	} else {
		t = new TBlock(difficulty);
	}  
     } else if (difficulty == 2) {
	if (n != -1) {  // check if seed has been supplied
		n = abs(rand()) % 7;
	}
	if (n == 0) {
		t = new SBlock(difficulty);
	} else if (n == 1) {
		t = new ZBlock(difficulty);
	} else if (n == 2) {
		t = new IBlock(difficulty);
	} else if (n == 3) {
		t = new OBlock(difficulty);
	} else if (n == 4) {
		t = new JBlock(difficulty);
	} else if (n == 5) {
		t = new LBlock(difficulty);
	} else {
		t = new TBlock(difficulty);
	}  
     } else if (difficulty == 3 || difficulty == 4) { // level 3 or 4
	if (n != -1) {  // check if seed has been supplied
		n = abs(rand()) % 9;
	}
	if (n == 0 || n == 1) {
		t = new SBlock(difficulty);
	} else if (n == 2 || n == 3) {
		t = new ZBlock(difficulty);
	} else if (n == 4) {
		t = new IBlock(difficulty);
	} else if (n == 5) {
		t = new OBlock(difficulty);
	} else if (n == 6) {
		t = new JBlock(difficulty);
	} else if (n == 7) {
		t = new LBlock(difficulty);
	} else {
		t = new TBlock(difficulty);
	}  
    }
    return t;
}


//returns a tetromino pointer of the desired type{L, J, O ... *}
Tetromino* LevelData::forceGenerate(std::string typeForced) {
	Tetromino *t;
	if (typeForced == "S") {
		t = new SBlock(difficulty);
	} else if (typeForced == "Z") {
		t = new ZBlock(difficulty);
	} else if (typeForced == "I") {
		t = new IBlock(difficulty);
	} else if (typeForced == "O") {
		t = new OBlock(difficulty);
	} else if (typeForced == "J") {
		t = new JBlock(difficulty);
	} else if (typeForced == "L") {
		t = new LBlock(difficulty);
	} else {
		t = new TBlock(difficulty);
	}  
	return t;
}

