#include "textdisplay.h"
#include "subject.h"
#include "tetromino.h"
#include <iostream>
#include <vector>

using namespace std;

//Constructor for textDisplay
TextDisplay::TextDisplay(){

	isMenu = false;
	boardSizeX = 11;
	boardSizeY = 18;
	gridP1 = vector<vector<char>> (boardSizeY, vector<char> (boardSizeX, ' '));
	gridP2 = vector<vector<char>> (boardSizeY, vector<char> (boardSizeX, ' '));
    nextPieceP1 = 'l';
    nextPieceP2 = 'l';
    isInit1, isInit2 = false;
}

void TextDisplay::notify(Subject &notifier){
	isMenu = notifier.getInfo()->menu;
if (notifier.getInfo()->playerID == 1) {
	gridP1 = notifier.getInfo()->grid;
	nextPieceP1 = notifier.getInfo()->nextTetro->getType();
	levelP1 = notifier.getInfo()->difficulty;
	scoreP1 = notifier.getInfo()->score;
	hasLostP1 = notifier.getInfo()->hasLost;
	playerID = notifier.getInfo()->playerID;
	isInit1 = true;
}
else if (notifier.getInfo()->playerID == 2) {
	
	gridP2 = notifier.getInfo()->grid;
	nextPieceP2 = notifier.getInfo()->nextTetro->getType();
	levelP2 = notifier.getInfo()->difficulty;
	scoreP2 = notifier.getInfo()->score;
	hasLostP2 = notifier.getInfo()->hasLost;
	playerID = notifier.getInfo()->playerID;
	isInit2 = true;
}
if (isInit1 && isInit2)
	cout << *this << endl;
}

ostream &operator<<(std::ostream &out, const TextDisplay &td)
{
	if (td.isMenu) { 
	out << "----------------------------" << endl;
	out << " || Select a punishment || " << endl;
		out << "(1) blind" << endl;
		out << "(2) heavy" << endl;
		out << "(3) force" << endl;
	out << "----------------------------" << endl;
	}
	else {
	//Prints top half of Game UI
	out << "Level:  " << td.levelP1 << "\t\t Level:  " << td.levelP2 << endl;
	out << "Score:  " << td.scoreP1 << "\t\t Score:  " << td.scoreP2 << endl;
	out << "--------------------------------------------------" << endl;
	
	//Prints playing field
	for (int x = td.boardSizeY - 1; x >= 0; x--){
		for (int y = 0; y < td.boardSizeX; y++){
			out << td.gridP1[x][y];
		}
		out << " \t\t ";
		for (int y = 0; y < td.boardSizeX; y++){
			out << td.gridP2[x][y];
		}
		out << endl;
	}

	//Prints bottom half of Game UI
	out << "--------------------------------------------------" << endl;
	if (td.playerID == 1){
	out << "Next: " << td.nextPieceP1 << endl;
	}
	else if (td.playerID == 2){
	out << "\t\t\t Next: " << td.nextPieceP2 << endl;
	}
	

	/* 
	Insert printing nextPiece method
	*/
	}
	return out;
}

void TextDisplay::display(const TextDisplay &td){
cout << td << endl; 
}

