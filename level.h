#ifndef _LEVEL_
#define _LEVEL_
#include <vector>

class Tetromino;

class LevelData{
	std::string path; // file name
	int difficulty;
	int seed;
	int index; // index of the seq vector we read from
	std::vector<std::string> seq; // holds the commands from the input file
    public:
	/*explicit*/ LevelData(int difficulty, std::string path = "", int seed = -1);
	Tetromino *generateTetromino(); //return a tetronimo pointer based on its difficulty
    Tetromino *forceGenerate(std::string typeForced); //returns a tetromino pointer of the desired type{L, J, O ... *}
	~LevelData() = default; //default destructor
};

#endif
