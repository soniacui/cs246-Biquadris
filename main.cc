#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main () {

  // input variables
  string s;
  string cmd;
  char c;
  int multiplier;

  // intialize our command list
  vector<string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
                             "drop", "levelup", "leveldown", "norandom", "random", 
                             "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart"};

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
        }
        else if (cmd == commands.at(1)) {
              cout << "command: right" << endl;
        }
        else if (cmd == commands.at(2)) {
                    cout << "command: down" << endl;
        }
        else if (cmd == commands.at(3)) {
              cout << "command: clockwise" << endl;
        }
        else if (cmd == commands.at(4)) {
              cout << "command: counterclockwise" << endl;
        }
        else if (cmd == commands.at(5)) {
                    cout << "command: drop" << endl;
        }
        else if (cmd == commands.at(6)) {
                    cout << "command: levelup" << endl;
          }
          else if (cmd == commands.at(7)) {
                    cout << "command: leveldown" << endl;
          }
          else if (cmd == commands.at(8)) {
              cout << "command: norandom" << endl;
          }
          else if (cmd == commands.at(9)) {
              cout << "command: random" << endl;
          }
          else if (cmd == commands.at(10)) {
              cout << "command: sequence" << endl;
          }
          else if (cmd == commands.at(11)) {
              cout << "command: I" << endl;
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
          }
              else {
          throw 1;
        }
    }
    catch (int e) {
        cout << "Unrecognized command. Please try again." << endl;
    }

  }
  
}

