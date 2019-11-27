#ifndef _LEVEL_
#define _LEVEL_

class Tetromino;

class LevelData{
	string path;
	int difficulty;
    public:
	LevelData(int difficulty, string path = "", int seed = -1);
	Tetromino *generateTetromino(); //return a tetronimo pointer based on its difficulty
    Tetromino *forceGenerate(string typeForced); //returns a tetromino pointer of the desired type{L, J, O ... *}
	~LevelData() = default; //default destructor
};

#endif
