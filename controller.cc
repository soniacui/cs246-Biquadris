#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "controller.h"
#include "board.h"
#include "tetromino.h"
#include "info.h"
// do i need to include something so i can print the board

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
        string s = ""
        string cmd = ""
        char c = 0;
        int multiplier = 0;
	// command list
        vector<string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
                             "drop", "levelup", "leveldown", "norandom", "random", 
                             "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart"};


  	// initialize displays
 	text_display1 = new Display{...};
 	text_display2 = new Display{...};
 	if (!textOnly) {
  		graphics_display1 = new Display{...}; //what do we do with graphics display?
 		graphics_display2 = new Display{...}; //it's not in the Board ctor
  	}

 	// initialize boards
  	b1 = Board{startLevel, 1, text_display1, seqfile1, seed};
  	b2 = Board{startLevel, 2, text_display2, seqfile2, seed};
  	b1.attach(b2); //attach boards to each other
  	b2.attach(b1);

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

// read command from stdin and call the corresponding action   
void Controller::readStdin() {

  // read input until EOF
  while (cin >> s) {

    cout << "creating stream: " << endl;
    istringstream iss(s);

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

	cout << "matching command: " << endl;
    	if (cmd == commands.at(0)) { 
       		cout << "command: left" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("left");
				if (!b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("left");
				if (!b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
   	}
   	else if (cmd == commands.at(1)) {
    		cout << "command: right" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("right");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("right");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
   	}
   	else if (cmd == commands.at(2)) {
    	        cout << "command: down" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("down");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("down");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
    	}
    	else if (cmd == commands.at(3)) {
    		cout << "command: clockwise" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("clockwise");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("clockwise");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
 	}
   	else if (cmd == commands.at(4)) {
    	 	cout << "command: counterclockwise" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("counterclockwise");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("counterclockwise");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
    	}
    	else if (cmd == commands.at(5)) {
    	        cout << "command: drop" << endl;
			if (b1.isTurn) {
				b1.performAction("drop");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("drop");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
  	}
 	else if (cmd == commands.at(6)) {
    	        cout << "command: levelup" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("levelup");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("levelup");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
  	}
  	else if (cmd == commands.at(7)) {
    	        cout << "command: leveldown" << endl;
		for (int i = 0; i < multiplier; ++i) {
			//check who's turn it is
			//perform action 
			if (b1.isTurn) {
				b1.performAction("leveldown");
				if (b1.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			} else {
				b2.performAction("leveldown");
				if (b2.isTurn) {      //if turn is over, stop performing action even if mutliplier isn't over
					break;
				}
			}
		}
  	}
  	else if (cmd == commands.at(8)) {
		string file;
    	 	cout << "command: norandom" << endl;
		cin >> file;       
		if (b1.isTurn) {
			b1.toggleRandom(file);
		} else {
			b2.toggleRandom(file);
		}

   	}
  	else if (cmd == commands.at(9)) {
    	 	cout << "command: random" << endl;
    	 	if (b1.isTurn) {
			b1.toggleRandom("");
		} else {
			b2.toggleRandom("");
		}	
  	}
   	else if (cmd == commands.at(10)) {
    	 	cout << "command: sequence" << endl;
		string file;
		cin >> file;
		ifstream ifs {file};
		//call controller with the commands in this file
  	}
   	else if (cmd == commands.at(11)) {                             //JK "FORCEBLOCK" IS FOR FORCING THE OTHER PERSON'S BLOCK
    	 	cout << "command: I" << endl;                          //IDK HOW TO FORCE MY OWN BLOCK YET
		for (int i = 0; i < multiplier; ++i) {			// ok jk this is fine; i just have to worry about taking input for SufferPunishment
			if (b1.isTurn) {
				b1.performAction("forceI");
				if (!b1.isTurn) {
					break;
				}
			} else {
				b2.performAction("forceI");
				if (!b2.isTurn) {
					break;
				}
			}
		}
  	}
  	else if (cmd == commands.at(12)) {
    	 	cout << "command: J" << endl;
   	}
    	else if (cmd == commands.at(13)) {
    	 	cout << "command: L" << endl;
   	}
   	else if (cmd == commands.at(14)) {
    	 	cout << "command: O" << endl;
   	}
   	else if (cmd == commands.at(15)) {
    	 	cout << "command: S" << endl;
   	}
    	else if (cmd == commands.at(16)) {
    	 	cout << "command: Z" << endl;
   	}
   	else if (cmd == commands.at(17)) {
    	 	cout << "command: T" << endl;
   	}
   	else if (cmd == commands.at(18)) {
    	 	cout << "command: restart" << endl;
		b1.restart();
		b2.restart();
   	} else {
		throw 1;
	}
        cout << display;
        if (checkGameOver()) {  // if game over, instant restart?
        	b1.restart();
		b2.restart();
		b1.attach(b2);
		b2.attach(b1);
   	}
    }
    catch (int e) {
        cout << "Unrecognized command. Please try again." << endl;
    }
  }
}

bool Controller::checkGameOver() {
	return (b1.isGameOver() || b2.isGameOver());
}

void Controller::multAction(int multiplier, string action) {
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
