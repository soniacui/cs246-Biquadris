#ifndef _CONTROLLER_
#define _CONTROLLER_
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "board.h"
#include "textdisplay.h"

class Controller {
	int argc;

	//boards
 	Board *b1;
  	Board *b2;

	//displays
	Observer *display;
	//TextDisplay text_display1;
	//TextDisplay text_display2;
	//Display graphics_display1;
	//Display graphics_display2;

	//command line arg variables
  	int seed;
  	int startLevel;
	std::string seqfile1;
	std::string seqfile2;
  	bool textOnly;

        // input variables
	std::string s;
	std::string cmd;
        char c;
        int multiplier;
	// command list
	std::vector<std::string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
                             "drop", "levelup", "leveldown", "norandom", "random", 
                             "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", 
 		             "blind", "heavy", "force"};
	char** argv;

	public:
	  Controller(int argc, char** argv);
	  void readArgs(); // read cmd line args
	  void readStdin(); // read commands from stdin
	  void readFile(std::string file); // read commands from file
	  void matchCmd(std::string s); // matches a command to s and executes the appropriate cmd
	  bool checkGameOver(); // checks if the game is over and restarts the game if it is
	  void multAction(int multipler, std::string action, std::string file = ""); // execute command multiplier times

	  

};

#endif
