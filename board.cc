#include "board.h"
#include "info.h"
#include "level.h"
#include <memory>
#include <vector>

using namespace std;

Board::Board(int difficulty, int playerID, Observer *display, string path, int seed): 
    difficulty{ difficulty }, playerID{ playerID } {
    grid(HEIGHT, vector<char>(WIDTH, ' ')); //initialize values
    isBlind = false;
    currPunish = "";
    sinceLastClear = 0;
    score = 0;
    deletedRow = -1;
    tetroFactory = LevelData(difficulty, path, seed);
    attach(display); //attach display as observer to board
    generateTetromino(); //make the starting tetromino
}

void Board::generateTetromino() {
    currTetro = tetroFactory.generateTetromino();
    tetrominoes.emplace_back(currTetro); //save a pointer to all tetrominoes generated in tetrominoes
    unique_ptr<Tetromino> ownedPtr { *currTetro }; //make unique pointer to give to observers
    observers.emplace_back(ownedPtr); //add tetromino as an observer
}

bool Board::checkDropped(TetrominoInfo tetroInfo) const {
    for (int i = 0; i < tetroInfo.absCoords.size(); i++) {
        if (grid[tetroInfo.absCoords[i][1] - 1][tetroInfo.absCoords[i][0]] != ' ') { //check if below each pixel of tetromino is not a free space
            for (int j = 0; j < tetroInfo.absCoords.size(); i++) {
                if ((tetroInfo.absCoords[j][0] == tetroInfo.absCoords[i][0]) &&
                    (tetroInfo.absCoords[j][1] == tetroInfo.absCoords[i][1] - 1))
                    continue; //continue when the not-free space in question is part of itself
            }
            return true //since there is no free space under a pixel of the tetromino, and it isn't itself, it has dropped
        }
    }
    return false;
}

void Board::clearLine() {
    bool linesCleared = 0;
    for (int i = 0; i < HEIGHT; i++) { //loop through rows
        bool toBeCleared = true;
        for (int j = 0; j < WIDTH; j++) { //loop through columns
            if (grid[i][j] == ' ')
                toBeCleared = false; //if there is a space in current line, do not remove line
        }
        if (toBeCleared) { //if current line has no spaces, perform removal
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
            if (linesCleared != 0 && (linesCleared / 2) == 0) { //every 2 lines cleared, choose effect for opponent
                choosePunishment();
            }
            sinceLastClear = 0; //reset counter for moves since last clear
            notifyObservers(); //notify to tetrominoes in case they might award extra points for removing completely
                               //notify to display to update grid as well
                               //notify opponent to suffer punishment if applicable
            currPunish = ""; //reset intent to punish
        }
    }
    score += difficulty + (linesCleared * linesCleared); //score increased for clearing lines
    if (linesCleared == 0) //if this step did not clear anything, increase counter
        sinceLastClear++;
    if (sinceLastClear == 5) {
        sinceLastClear = 0;
        if (difficulty == 4)
            sufferPunishment("force*"); //if it is level 4 and no lines cleared in 5 turns, suffer 1x1 block
    }
    isBlind = false; //reset blindness, if blind
    generateTetromino(); //make a new tetromino for next step, clears force effect and heavy effect
}

void Board::toggleRandom(string newPath) {
    tetroFactory = LevelData(difficulty, newPath); //make new factory with requested randomness
}

bool Board::isGameOver() {

}

void Board::restart() {

}

void Board::performAction(string action) { //handles input as a distinct unique string, calls action on current block
    if (action == "left" || action == "right" || action == "down") {
        currTetro->move(action);
    }
    else if (action == "clockwise" || action == "counterclockwise") {
        currTetro->rotate(action);
    }
    else {
        currTetro->drop();
    }
}

void Board::choosePunishment() {
    //somehow get input from user to decide on punishment
    if () //blind case
        currPunish = "blind";
    else if () //heavy case
        currPunish = "heavy";
    else if () { //force case
        if () //I force
            currPunish = "forceI";
        else if () //J force
            currPunish = "forceJ";
        else if () //L force
            currPunish = "forceL";
        else if () //O force
            currPunish = "forceO";
        else if () //S force
            currPunish = "forceS";
        else if () //Z force
            currPunish = "forceZ";
        else if () //T force
            currPunish = "forceT";
    }
}

void Board::sufferPunishment(string effect) {
    if (effect == "blind")
        isBlind = true;
    else if (effect == "forceI") {
        currTetro = tetroFactory.forceGenerate("I"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr { *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "forceJ") {
        currTetro = tetroFactory.forceGenerate("J"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "forceL") {
        currTetro = tetroFactory.forceGenerate("L"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "forceO") {
        currTetro = tetroFactory.forceGenerate("O"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "forceS") {
        currTetro = tetroFactory.forceGenerate("S"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "forceZ") {
        currTetro = tetroFactory.forceGenerate("Z"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "forceT") {
        currTetro = tetroFactory.forceGenerate("T"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "force*") {
        //currTetro does not change, this is a strict add-on

        Tetromino *specialTetro = tetroFactory.forceGenerate("*"); //make a specific tetro *
        unique_ptr<Tetromino> starPtr{ *specialTetro }; //make it a unique ptr

        //nothing is popped off since this is a strict addition

        observers.emplace_back(starPtr); //add starTetromino to observers (award potential points), not added to tetrominoes since it cannot be forced
        starPtr->drop(); //this immediately drops the starBlock
    }
    else if (effect == "heavy")
        currTetro->increaseSpeed(2);
    else
        return;
}

void Board::notify(Subject &notifier) {
    Info *info = notifier.getInfo(); //get relevant information from caller
    if (info->infoType == "tetromino") { //if caller is a tetromino
        TetrominoInfo *castedInfo = static_cast<TetrominoInfo *>(info);
        if (castedInfo->isDeleted) { //case for tetromino has been removed from board
            score += (castedInfo->value + 1) * (castedInfo->value + 1); //add points
            deletedRow = -1; //reset deleted row to default
            if (score > Board.highScore) //change static highscore if my score is greater
                Board.highScore = score;
        }
        else { //handling tetromino representation on internal grid
            for (int i = 0; i < info->absCoords.size(); i++) {
                grid[info->previously[i][1]][info->previously[i][0]] = ' '; //fill old location
                grid[info->absCoords[i][1]][info->absCoords[i][0]] = info->type; //new location
            }
            if (checkDropped(*info)) //check if the tetromino has dropped to the bottom
                clearLine(); //complete end of turn actions, add points clear lines etc.
        }
    }
    else { //if caller is opponent board, only case is to suffer effect
        string effect = static_cast<BoardInfo *>(info)->punishType;
        sufferPunishment(effect);
    }
    notifyObservers(); //relay message to observers, namely the displays
}

Info *Board::getInfo() const {
    vector<vector<char>> displayGrid = grid; //buffer grid to the display to show something differently than represented
    if (isBlind) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i >= 2 && i <= 11 && j >= 2 && j <= 8)
                    displayGrid[i][j] = '?'; //set grid locations that are hidden to ?
            }
        }
    }
    unique_ptr<BoardInfo> bInfo { new BoardInfo(displayGrid, currPunish, deletedRow, "board") };
    return bInfo;
}