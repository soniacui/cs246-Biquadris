#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "tetromino.h"
#include "level.h"

using namespace std;

LevelData::LevelData(int difficulty, string path, int seed): difficulty{difficulty}, path{path}, seed{seed} {
	vector<string> seq;
	string s = "";
	/*if (path != "") {             //load input seq  // ****** this requires that a new LevelData object is created every time the user calls norandom xxx
            ifstream input (path);                      //        so we can read from the top of the file again
            while (path >> s) {
		input.push(s);
	    }
	}*/
        if (seed != -1) {
	    srand(seed);
	}
}

Tetromino* LevelData::generateTetromino() { // potential problem: if user calls norandom xxx, random, does LevelData still retain the old filename?

    //current problems: 
    // see *******s
    // not quite sure if seed works properly
    // need to add vector to uml/.h file

    //generate normally
    //norandom/random (gives blocks)
    //seed
    
    int n = -1;
    Tetromino *t;
    /*if (difficulty == 0 || path != "") { // if user has called norandom with a file path
	s = seq.at(0);              // ********* check if empty? 
        seq.pop_front();
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
    */
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

