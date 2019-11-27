#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include level.h

using namespace std;

LevelData::LevelData(int difficulty, string path = "", int seed = -1) : level{difficulty}, path{path}, seed{seed} {
	vector<string> seq;
	string s;
	if (path != "") {             //load input seq  // ****** this requires that a new LevelData object is created every time the user calls norandom xxx
            ifstream input {path};                      //        so we can read from the top of the file again
            while (path >> s) {
		input.push(s);
	    }
	}
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
    if (level == 0 || path != "") { // if user has called norandom with a file path
	s = seq.at(0);              // ********* check if empty? 
        seq.pop_front();
	if (s == "S") {
		t = new SBlock{};
	} else if (s == "Z") {
		t = new ZBlock{};
	} else if (s == "I") {
		t = new IBlock{};
	} else if (s == "O") {
		t = new OBlock{};
	} else if (s == "J") {
		t = new JBlock{};
	} else if (s == "L") {
		t = new LBlock{};
	} else if (s == "T") {
		t = new TBlock{};
	}
	return t;
    if (seed != -1) {  // if user has supplied a seed
	n = abs(rand()) % 7;        
    } 
    if (level == 1) {
	if (n != -1) { // check if seed has been supplied
		n = abs(rand()) % 12; 
	}
	if (n == 0) {
		t = new SBlock{};
	} else if (n == 1) {
		t = new ZBlock{};
	} else if (n == 2 || n == 3) {
		t = new IBlock{};
	} else if (n == 4 || n == 5) {
		t = new OBlock{};
        } else if (n == 6 || n == 7) {
		t = new JBlock{};
	} else if (n == 8 || n == 9) {
		t = new LBlock{};
	} else {
		t = new TBlock{};
	}  
     } else if (level == 2) {
	if (n != -1) {  // check if seed has been supplied
		n = abs(rand()) % 7;
	}
	if (n == 0) {
		t = new SBlock{};
	} else if (n == 1) {
		t = new ZBlock{};
	} else if (n == 2) {
		t = new IBlock{};
	} else if (n == 3) {
		t = new OBlock{};
	} else if (n == 4) {
		t = new JBlock{};
	} else if (n == 5) {
		t = new LBlock{};
	} else {
		t = new TBlock{};
	}  
     } else if (level == 3 || level == 4) { // level 3 or 4
	if (n != -1) {  // check if seed has been supplied
		n = abs(rand()) % 9;
	}
	if (n == 0 || n == 1) {
		t = new SBlock{};
	} else if (n == 2 || n == 3) {
		t = new ZBlock{};
	} else if (n == 4) {
		t = new IBlock{};
	} else if (n == 5) {
		t = new OBlock{};
	} else if (n == 6) {
		t = new JBlock{};
	} else if (n == 7) {
		t = new LBlock{};
	} else {
		t = new TBlock{};
	}  
    }
    return t;

}

