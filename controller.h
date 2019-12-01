#ifndef _CONTROLLER_
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Controller {
	int argc;
	char* argv[];

	//boards
 	Board b1;
  	Board b2;

	//displays
	Display *text_display1;
	Display *text_display2;
	Display *graphics_display1;
	Display *graphics_display2;

	//command line arg variables
  	int seed;
  	int startLevel;
  	string seqfile1;
  	string seqfile2;
  	bool textOnly;

        // input variables
        string s;
        string cmd;
        char c;
        int multiplier;
	// command list
        vector<string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
                             "drop", "levelup", "leveldown", "norandom", "random", 
                             "sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", 
 		             "blind", "heavy", "force"};

	public:
	  Controller(Board &b1, Board &b2);
	  void readArgs(); // read cmd line args
	  void readStdin(); // read commands from stdin
	  void readFile(string file); // read commands from file
	  void matchCmd(string s); // matches a command to s and executes the appropriate cmd
	  bool checkGameOver(); // checks if the game is over and restarts the game if it is
	  void multAction(int multipler, string action, string file = ""); // execute command multiplier times

	  

};

endif;
