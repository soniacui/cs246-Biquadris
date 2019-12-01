#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"

class TextDisplay: public Observer 
{
	bool isMenu;
	bool hasLostP1;
	bool hasLostP2;
	int boardSizeX;
	int boardSizeY;
 	std::vector<std::vector<char>> gridP1
 	std::vector<std::vector<char>> gridP2
	char nextPieceP1;
	char nextPieceP2;
	int levelP1;
	int levelP2;
	int scoreP1;
	int scoreP2;

 public:
  //Constructor
  TextDisplay();

  //Recieves board and tetromino information for updating data
  void notify(Subject<Grid, NextPiece, Level, Score> &whoNotified);

  //Prints the info textdisplay has
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
