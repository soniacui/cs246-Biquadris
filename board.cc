#include "board.h"
#include "info.h"
#include "level.h"
#include <memory>
#include <vector>
#include <iostream> /////////////////////rem

using namespace std;

int Board::highScore = 0;

Board::Board(int difficulty, int playerID, Observer *display, string path, int seed): 
    tetroFactory {LevelData(difficulty, playerID, path, seed)}, display{ display }, path{ path }, seed{ seed }, difficulty{ difficulty }, playerID{ playerID } {
    grid = vector<vector<char>> (HEIGHT, vector<char>(WIDTH, ' ')); //initialize values
    isBlind = false;
    currTetro = nullptr;
    nextTetro = nullptr;
    menu = false;
    hasLost = false;
    currPunish = "";
    sinceLastClear = 0;
    score = 0;
    deletedRow = -1;
    if (playerID == 1)
        isTurn = true;
    else
        isTurn = false;
    //tetroFactory(difficulty, path, seed);
    attach(display); //attach display as observer to board
    generateTetromino(); //make the starting tetromino
    notifyObservers(); //display starting state
    //cout << playerID << observers.size() << currTetro->observers.size() << endl;
}

void Board::drawToGrid(Tetromino *currTetro) {
    shared_ptr<TetrominoInfo>initInfo = currTetro->getTetroInfo();
    cout << initInfo->absCoords.size() << endl;
    cout << initInfo->type << endl;
    for (int i = 0; i < initInfo->absCoords.size(); i++) {
        cout << initInfo->absCoords[i][1] << ", " << initInfo->absCoords[i][0] << endl;
        grid[initInfo->absCoords[i][1]][initInfo->absCoords[i][0]] = initInfo->type;
    }
}

void Board::generateTetromino() {
    if (nextTetro == nullptr) {
        currTetro = tetroFactory.generateTetromino(grid);
	//cout << "following is tetro's" << endl;
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.emplace_back(currTetro); //save a pointer to all tetrominoes generated in tetrominoes
        attach(currTetro); //add tetromino as an observer
    }
    else {
        currTetro = nextTetro; //replace currTetro with nextTetro
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.emplace_back(nextTetro); //put the next tetromino onto list of tetrominoes ptrs
        attach(nextTetro); //put next tetromino as an observer
        currTetro->updateGrid(grid);
    }
    if (isGameOver(*currTetro->getTetroInfo())) {
        hasLost = true;
        drawToGrid(currTetro);
        notifyObservers(); //display ending screen
    }
    drawToGrid(currTetro);
    nextTetro = tetroFactory.generateTetromino(grid); //make new next tetromino
}

bool Board::checkDropped(TetrominoInfo tetroInfo) const {
	cout << "checkecheckechk" << endl;
    if (tetroInfo.isDropped)
        return true;
    if (tetroInfo.isHeavy || tetroInfo.speed != 0) {
        for (int i = 0; i < tetroInfo.absCoords.size(); i++) {
            if (grid[tetroInfo.absCoords[i][1] - 1][tetroInfo.absCoords[i][0]] != ' ') { //check if below each pixel of tetromino is not a free space
                for (int j = 0; j < tetroInfo.absCoords.size(); i++) {
                    if ((tetroInfo.absCoords[j][0] == tetroInfo.absCoords[i][0]) &&
                        (tetroInfo.absCoords[j][1] == tetroInfo.absCoords[i][1] - 1))
                        continue; //continue when the not-free space in question is part of itself
                }
                return true; //since there is no free space under a pixel of the tetromino, and it isn't itself, it has dropped
            }
        }
        return false;
    }
    return false;
}

void Board::clearLine() {
	cout << "NEWWWWWWWWW" << endl;
    int linesCleared = 0;
    for (int i = 0; i < HEIGHT; i++) { //loop through rows
        bool toBeCleared = true;
        for (int j = 0; j < WIDTH; j++) { //loop through columns
            if (grid[i][j] == ' ')
                toBeCleared = false; //if there is a space in current line, do not remove line
        }
        if (toBeCleared) { //if current line has no spaces, perform removal
		cout << "clearing: " << i << endl;
            deletedRow = i;
            for (int y = 0; y < HEIGHT; y++) { //from bottom up
                if (y == HEIGHT - 1) { //very first row is always fresh
                    grid[y] = vector<char>(WIDTH, ' ');
                    continue;
                }
                if (y >= deletedRow) //replace current row with the one above it if it is or above the deleted line
                    grid[y] = grid[y + 1];
            }
            linesCleared++;
	    notifyObservers();
	    cout << "tis prob wonr run" << endl;
	    deletedRow = -1; //reset
            if (linesCleared != 0 && ((linesCleared % 2) == 0)) { //every 2 lines cleared, choose effect for opponent
                menu = true; //set menu to true, allow only commands that deal with menu
                notifyObservers();
                menu = false; //allow regular commands to have effect again
            }
            sinceLastClear = 0; //reset counter for moves since last clear
            //notifyObservers(); //notify to tetrominoes in case they might award extra points for removing completely
                               //notify to display to update grid as well
                               //notify opponent to suffer punishment if applicable
            currPunish = ""; //reset intent to punish
        }
    }
    if (linesCleared == 0) //if this step did not clear anything, increase counter
        sinceLastClear++;
    else
        score += difficulty + (linesCleared * linesCleared); //score increased for clearing lines
    if (sinceLastClear == 5) {
        sinceLastClear = 0;
        if (difficulty == 4)
            sufferPunishment("*"); //if it is level 4 and no lines cleared in 5 turns, suffer 1x1 block
    }
    isBlind = false; //reset blindness, if blind
    isTurn = false; //end turn
    generateTetromino(); //make a new tetromino for next step, clears force effect and heavy effect
}

void Board::restart() {
    currTetro = nullptr; //reset pointers
    nextTetro = nullptr;
    tetrominoes.clear();

    grid = vector<vector<char>> (HEIGHT, vector<char>(WIDTH, ' ')); //initialize values
    isBlind = false;
    menu = false;
    hasLost = false;
    currPunish = "";
    sinceLastClear = 0;
    score = 0;
    deletedRow = -1;
    if (playerID == 1)
        isTurn = true;
    else
        isTurn = false;
    tetroFactory = LevelData(difficulty, playerID, path, seed);
    generateTetromino(); //make the starting tetromino
    notifyObservers(); //display starting state
}

void Board::toggleRandom(string newPath) {
    if (difficulty == 3 || difficulty == 4 && !menu) {
        tetroFactory = LevelData(difficulty, playerID, newPath); //remake factory with path to sequence with requested randomness
    }
    notifyObservers();
}

bool Board::isGameOver(TetrominoInfo newest) {
    for (int i = 0; i < newest.absCoords.size(); i++) {
        if (grid[newest.absCoords[i][1]][newest.absCoords[i][0]] != ' ') //if any spots of the new block overlap with an existing one, GG
            return true;
    }
    return false;
}

void Board::performAction(string action, string newPath) { //handles input as a distinct unique string, calls action on current block
    cout << "IN ACTION SELECTION" << endl;
    if (action == "left" || action == "right" || action == "down") {
        if (!menu)
		cout << "aaaaaaaaaa" << endl;
            currTetro->move(action);
    }
    else if (action == "clockwise" || action == "counterclockwise") {
        if (!menu)
            currTetro->rotate(action);
    }
    else if (action == "drop") {
        if (!menu)
            currTetro->drop();
    }
    else if (action == "levelup") {
        if (difficulty != 4 && !menu) {
            difficulty++;
            tetroFactory = LevelData(difficulty, playerID, path, seed); //make new factory for blocks
        }
        notifyObservers();
    }
    else if (action == "leveldown") {
        if (difficulty != 0 && !menu) {
            difficulty--;
            tetroFactory = LevelData(difficulty, playerID, path, seed); //make new factory for blocks
        }
        notifyObservers();
    }
    else if (action == "blind") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "blind";
        }
    }
    else if (action == "heavy") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "heavy";
        }
    }
    else if (action == "forceL") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "L";
        }
	else{
		sufferPunishment("L");
		notifyObservers();
	}
    }
    else if (action == "forceI") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "I";
        }
        else{
                sufferPunishment("I");
                notifyObservers();
        }

    }
    else if (action == "forceZ") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "Z";
        }
        else{
                sufferPunishment("Z");
                notifyObservers();
        }

    }
    else if (action == "forceT") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "T";
        }
        else{
                sufferPunishment("T");
                notifyObservers();
        }
    }
    else if (action == "forceO") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "O";
        }
        else{
                sufferPunishment("O");
                notifyObservers();
        }
    }
    else if (action == "forceS") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "S";
        }
        else{
                sufferPunishment("S");
                notifyObservers();
        }
    }
    else if (action == "forceJ") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "J";
        }
        else{
                sufferPunishment("J");
                notifyObservers();
        }
    }
    /*
    else { //the remaining commands will be to force own block
        if (!menu) {
            sufferPunishment(action);
            notifyObservers();
        }
    }
    */
}

void Board::deleteTetro(Tetromino *destroy) {
    shared_ptr<TetrominoInfo> tempInfo = destroy->getTetroInfo(); //get info from current tetro
    for (int i = 0; i < tempInfo->absCoords.size(); i++) {
        grid[tempInfo->absCoords[i][1]][tempInfo->absCoords[i][0]] = ' '; //fill in its location
    }
}

void Board::sufferPunishment(string effect) {
    if (effect == "blind")
        isBlind = true;
    else if (effect == "I") {
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "I"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "J") {
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "J"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "L") {
	    cout << "11111" << endl;
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "L"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "O") {
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "O"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "S") {
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "S"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "Z") {
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "Z"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "T") {
        deleteTetro(currTetro); //removes current tetro off the grid
        remove(tetrominoes.size()); //delete previous current in observers and tetrominoes
        currTetro = tetroFactory.forceGenerate(grid, "T"); //make a specific tetro as current
        currTetro->attach(this); //set this board as observer to the tetro
        tetrominoes.pop_back();
        attach(currTetro); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
        if (isGameOver(*currTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(currTetro);
            notifyObservers(); //display ending screen
        }
        drawToGrid(currTetro);
    }
    else if (effect == "*") {
        //currTetro does not change, this is a strict add-on

        Tetromino *specialTetro = tetroFactory.forceGenerate(grid, "*"); //make a specific tetro *
        specialTetro->attach(this); //set this board as observer to the tetro

        //nothing is popped off since this is a strict addition

        attach(specialTetro); //add starTetromino to observers (award potential points), not added to tetrominoes since it cannot be forced
        if (isGameOver(*specialTetro->getTetroInfo())) {
            hasLost = true;
            drawToGrid(specialTetro);
            notifyObservers(); //display ending screen
        }
        specialTetro->drop(); //this immediately drops the starBlock
    }
    else if (effect == "heavy")
        currTetro->toggleHeavy();
    else
        return;
}

void Board::notify(Subject &notifier) {
	cout << "BOARD HAS BEEN NOTIFIED" << endl;
    shared_ptr<TetrominoInfo>tInfo = notifier.getTetroInfo(); //get relevant information from caller
    cout << "HMMM" << endl;
    shared_ptr<BoardInfo>bInfo = notifier.getInfo();
    cout << "bbbbbbbbbb" << endl;
    cout << tInfo << endl;
    cout << bInfo << endl;
    if (tInfo != nullptr) { //if caller is a tetromino
	    cout << "TETRO" << endl;
        if (tInfo->isDeleted) { //case for tetromino has been removed from board
		cout << "SOMETHING HAS BEEN TOTAL DELETED" << endl;
            score += (tInfo->value + 1) * (tInfo->value + 1); //add points
	    if (score > Board::highScore) //change static highscore if my score is greater
                Board::highScore = score;
	    int tempDeleted = deletedRow;
            deletedRow = -1; //temporarily reset deleted row to default so no recalls of other tetro
	    notifyObservers();
	    deletedRow = tempDeleted;
	    return;
            //if (score > Board::highScore) //change static highscore if my score is greater
            //    Board::highScore = score;
        }
        else { //handling tetromino representation on internal grid
		    cout << "dddddddd" << endl;
            //a move done to an existing nondropped tetromino
		    cout << tInfo->absCoords.size() << endl;
		    cout << "f.5555555" << endl;
		    for (int i = 0; i < tInfo->absCoords.size(); i++) {
			    cout << tInfo->absCoords[i][0]  << ", " << tInfo->absCoords[i][1] << endl;
		        grid[tInfo->previously[i][1]][tInfo->previously[i][0]] = ' '; //fill old location
            }
            for (int i = 0; i < tInfo->absCoords.size(); i++) {
                grid[tInfo->absCoords[i][1]][tInfo->absCoords[i][0]] = tInfo->type; //new location
            }
		    cout << "gggggggggggg" << endl;
            if (checkDropped(*tInfo)) //check if the tetromino has dropped to the bottom
                clearLine(); //complete end of turn actions, add points clear lines etc.
        }
    }
    else { //if caller is opponent board, only case is to suffer effect
	    if (bInfo->punishType != "")
        	    sufferPunishment(bInfo->punishType);
	    else if (!bInfo->isTurn && currPunish == "")
		    isTurn = true;
	    else
		    return;
    }
    notifyObservers(); //relay message to observers, namely the displays
}

shared_ptr<BoardInfo> Board::getInfo() const {
    vector<vector<char>> displayGrid = grid; //buffer grid to the display to show something differently than represented
    if (isBlind) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i >= 2 && i <= 11 && j >= 2 && j <= 8)
                    displayGrid[i][j] = '?'; //set grid locations that are hidden to ?
            }
        }
    }

    shared_ptr<BoardInfo> bInfo{ new BoardInfo(displayGrid, currPunish, difficulty, score, playerID, deletedRow, nextTetro, isTurn, menu, hasLost, "board") };
    return bInfo;
}

shared_ptr<TetrominoInfo> Subject::getTetroInfo() { return nullptr; }
