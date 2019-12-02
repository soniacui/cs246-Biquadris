#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "controller.h"
#include "board.h"
#include "tetromino.h"
#include "info.h"
#include "textdisplay.h"
//#include "graphicsdisplay.h"

using namespace std;

//ctor
Controller::Controller(int argc, char* argv[]) : argc{argc}, argv{argv} {
	//command line arg variables
	seed = -1;
	startLevel = 0;
  	seqfile1 = "";
  	seqfile2 = "";
  	textOnly = false;
	readArgs(); // update command line arg variables

	// input variables
        s = "";
        cmd = "";
        c = 0;
        multiplier = 0;
	// command list
        vector<string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
                             "drop", "levelup", "leveldown", "norandom", "random", 
                             "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart"};


  	// initialize displays
 	text_display1 = new TextDisplay();
 	text_display2 = new TextDisplay();
 	if (!textOnly) {
  		//graphics_display1 = new GraphicsDisplay(); //what do we do with graphics display?
 		//graphics_display2 = new GraphicsDisplay(); //it's not in the Board ctor
  	}

 	// initialize boards
	LevelData lvl1 = LevelData(startLevel, seqfile1, seed);
	LevelData lvl2 = LevelData(startLevel, seqfile2, seed);
  	b1 = Board{lvl1, text_display1, seqfile1, seed, startLevel, 1};
  	b2 = Board{lvl2, text_display2, seqfile2, seed, startLevel, 2};
  	b1.attach(&b2); //attach boards to each other
  	b2.attach(&b1);

}

// read cmd line args
void Controller::readArgs() {
  //check for command line arguments
  for (int i = 0; i < argc; ++i) {
	if (string(argv[i]) == "-text") {
		textOnly = true;
	} else if (string(argv[i]) == "-seed") {
		seed = atoi(argv[i + 1]);
	} else if (string(argv[i]) == "-scriptfile1") {
		seqfile1 = argv[i + 1];
	} else if (string(argv[i]) == "-scriptfile2") {
		seqfile2 = argv[i + 1];
	} else if (string(argv[i]) == "-startlevel") {
		startLevel = atoi(argv[i + 1]);
	}
	//cout << "arg " << i << ": "<< argv[i] << endl;
  }
  //cout << "seed: " << seed << endl;
  //cout << "startLevel: " << startLevel << endl;
  //cout << "seqfile1: " << seqfile1 << endl;
  //cout << "seqfile2: " << seqfile2 << endl;


}

void Controller::matchCmd(string s) {
    cout << "creating stream: " << endl;
    istringstream iss (s);

    // check if command contains a multiplier
    cout << "peeking: " << endl;
    c = iss.peek();
    cout << "PEEKED c: " << c << endl;
    if (c >= '0' && c <= '9') {
	iss >> multiplier;
        cout << "multiplier: " << multiplier << endl;

    }

    try { //throw smth if failed
	int matches = 0;
   	int matched_index = 0;
	
	cout << "checking matches: " << endl;
	// check if the user's command matches an existing command
   	if (iss >> cmd) {
		cout << "user's command: " << cmd << endl;
		for (int i = 0; i < commands.size(); ++i) {
		    if (commands.at(i).substr(0, cmd.length()) == cmd) {
			matched_index = i;
			++matches;
			cout << "matched index: " << matched_index << endl;
     	       }
    	    }
   	}

	// if the user entered valid input, there should only be 1 match
  	if (matches != 1) {
		throw 1;       //throw exception if invalid input
	}

	cmd = commands.at(matched_index);
    if (!b1.menu && !b2.menu) {
    	cout << "matching command: " << endl;
    	if (cmd == commands.at(0)) { 
       		cout << "command: left" << endl;
		multAction(multiplier, "left");
   	}
   	else if (cmd == commands.at(1)) {
    		cout << "command: right" << endl;
		multAction(multiplier, "right");   	
	}
   	else if (cmd == commands.at(2)) {
    	        cout << "command: down" << endl;
		multAction(multiplier, "down");  
    	}
    	else if (cmd == commands.at(3)) {
    		cout << "command: clockwise" << endl;
		multAction(multiplier, "clockwise"); 
 	}
   	else if (cmd == commands.at(4)) {
    	 	cout << "command: counterclockwise" << endl;
		multAction(multiplier, "counterclockwise"); 
    	}
    	else if (cmd == commands.at(5)) {
    	        cout << "command: drop" << endl;
		multAction(1, "drop"); //ignores multiplier
  	}
 	else if (cmd == commands.at(6)) {
    	        cout << "command: levelup" << endl;
		multAction(multiplier, "levelup"); 
  	}
  	else if (cmd == commands.at(7)) {
    	        cout << "command: leveldown" << endl;
		multAction(multiplier, "leveldown"); 
  	}
  	else if (cmd == commands.at(8)) {
		string file;
    	 	cout << "command: norandom" << endl;
		cin >> file;       
		multAction(1, "norandom", file);
   	}
  	else if (cmd == commands.at(9)) {
    	 	cout << "command: random" << endl;
		multAction(1, "random");	
  	}
   	else if (cmd == commands.at(10)) {
    	 	cout << "command: sequence" << endl;
		string file;
		cin >> file;
		multAction(1, "sequence", file);
  	}
   	else if (cmd == commands.at(11)) {                             
    	 	cout << "command: I" << endl;                          
		multAction(multiplier, "forceI");
  	}
  	else if (cmd == commands.at(12)) {
    	 	cout << "command: J" << endl;
		multAction(multiplier, "forceJ");
   	}
    	else if (cmd == commands.at(13)) {
    	 	cout << "command: L" << endl;
		multAction(multiplier, "forceL");
   	}
   	else if (cmd == commands.at(14)) {
    	 	cout << "command: O" << endl;
		multAction(multiplier, "forceO");
   	}
   	else if (cmd == commands.at(15)) {
    	 	cout << "command: S" << endl;
		multAction(multiplier, "forceS");
   	}
    	else if (cmd == commands.at(16)) {
    	 	cout << "command: Z" << endl;
		multAction(multiplier, "forceZ");
   	}
   	else if (cmd == commands.at(17)) {
    	 	cout << "command: T" << endl;
		multAction(multiplier, "forceT");
   	}
   	else if (cmd == commands.at(18)) {
    	 	cout << "command: restart" << endl;
		multAction(1, "restart");
   	} else {
		throw 1;
	}
     } else {
	   if (cmd == commands.at(19)) {
		cout << "command: blind" << endl;
		multAction(1, "blind");
	   } else if (cmd == commands.at(20)) {
		cout << "command: heavy" << endl;
		multAction(1, "heavy");
	   } else if (cmd == commands.at(18)) {
		cout << "command: force" << endl;
		string type;
		cin >> type;
		multAction(1, "force" + type);
	   }
     }
        cout << text_display1;
        if (checkGameOver()) {  // if game over, instant restart?
		multAction(1, "restart");
   	}

    }
   
    catch (int e) {
        cout << "Unrecognized command. Please try again." << endl;
    }

}

// read command from stdin and call the corresponding action   
void Controller::readStdin() {

  // read input until EOF
  while (cin >> s) {
	matchCmd(s);
  }
}

// create file and read from file, call corresponding action
void Controller::readFile(string file) {

  // read input from file until EOF
  ifstream ifs {file};
  string s;
  while (ifs >> s) {
     matchCmd(s);
   
  }
}

bool Controller::checkGameOver() {
	return (b1.isGameOver() || b2.isGameOver());
}

void Controller::multAction(int multiplier, string action, string file = "") {
	if (action == "norandom" || action == "random") {
		if (b1.isTurn) {
			b1.toggleRandom(file);
		} else {
			b2.toggleRandom(file);
		}
	} else if (action == "sequence") {
		readFile(file);
	} else if (action == "restart") { //restart
        	b1.restart();
		b2.restart();
		b1.attach(&b2);
		b2.attach(&b1);
	} else if (action == "blind" || action == "heavy") { //will not end turn
		if (b1.isTurn) {
			b1.performAction(action);
		} else {
			b2.performAction(action);
		}
	} else {   //can potentially end turns
		//move/rotate/drop/force
		for (int i = 0; i < multiplier; ++i) {
			if (b1.isTurn) {
				b1.performAction(action);
				if (!b1.isTurn) {
					break;
				}
			} else {
				b2.performAction(action);
				if (!b2.isTurn) {
					break;
				}
			}
		}
	}
}
