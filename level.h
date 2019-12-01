#ifndef _LEVEL_
#define _LEVEL_

class Tetromino;

class LevelData{
	string path; // file name
	int difficulty;
	int seed;
	int index; // index of the seq vector we read from
	vector<string> seq; // holds the commands from the input file
    public:
	LevelData(int difficulty, string path = "", int seed = -1);
	Tetromino *generateTetromino(); //return a tetronimo pointer based on its difficulty
    Tetromino *forceGenerate(string typeForced); //returns a tetromino pointer of the desired type{L, J, O ... *}
	~LevelData() = default; //default destructor
};

#endif
