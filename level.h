#ifndef _LEVEL_
#define _LEVEL_

class Tetromino;

class LevelData{
	string path;
	int difficulty;
    public:
	LevelData(int difficulty, string path = "");
	Tetromino *generateTetromino(); //return a tetronimo pointer based on its difficulty
	~LevelData() = default; //default destructor
};

#endif
