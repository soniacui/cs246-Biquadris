#include "board.h"
#include "info.h"
#include "level.h"
#include <memory>
#include <vector>

using namespace std;

Board::Board(int difficulty, int playerID, Observer *display, string path, int seed): 
    difficulty{ difficulty }, display{ display }, path{ path }, seed{ seed }, playerID{ playerID } {
    grid(HEIGHT, vector<char>(WIDTH, ' ')); //initialize values
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
    tetroFactory = LevelData(difficulty, path, seed);
    attach(display); //attach display as observer to board
    generateTetromino(); //make the starting tetromino
    notifyObservers(); //display starting state
}

void Board::generateTetromino() {
    if (nextTetro.get() == nullptr) {
        currTetro = tetroFactory.generateTetromino();
        tetrominoes.emplace_back(currTetro); //save a pointer to all tetrominoes generated in tetrominoes
        unique_ptr<Tetromino> ownedPtr{ *currTetro }; //make unique pointer to give to observers
        observers.emplace_back(ownedPtr); //add tetromino as an observer
    }
    else {
        currTetro = nextTetro.get(); //replace currTetro with nextTetro
        tetrominoes.emplace_back(nextTetro.get()); //put the next tetromino onto list of tetrominoes ptrs
        observers.emplace_back(nextTetro); //put next tetromino as an observer
    }

    nextTetro = make_unique<Tetromino>(tetroFactory.generateTetromino()); //make new next tetromino
}

bool Board::checkDropped(TetrominoInfo tetroInfo) const {
    if (tetroInfo.isDropped)
        return true;
    if (tetroInfo.isHeavy) {
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
                menu = true; //set menu to true, allow only commands that deal with menu
                notifyObservers();
                menu = false; //allow regular commands to have effect again
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
            sufferPunishment("*"); //if it is level 4 and no lines cleared in 5 turns, suffer 1x1 block
    }
    isBlind = false; //reset blindness, if blind
    isTurn = false; //end turn
    generateTetromino(); //make a new tetromino for next step, clears force effect and heavy effect
}

void Board::restart() {
    currTetro = nullptr; //reset pointers
    nextTetro.reset();
    tetrominoes.clear();

    grid(HEIGHT, vector<char>(WIDTH, ' ')); //initialize values
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
    tetroFactory = LevelData(difficulty, path, seed);
    generateTetromino(); //make the starting tetromino
    notifyObservers(); //display starting state
}

void Board::toggleRandom(string newPath) {
    tetroFactory = LevelData(difficulty, newPath); //make new factory with requested randomness
}

bool Board::isGameOver(TetrominoInfo newest) {
    for (int i = 0; i < newest.absCoords.size(); i++) {
        if (grid[newest.absCoords[i][1][newest.absCoords[i][0]] != ' ']) //if any spots of the new block overlap with an existing one, GG
            return true;
    }
    return false;
}

void Board::performAction(string action, string newPath) { //handles input as a distinct unique string, calls action on current block
    if (action == "left" || action == "right" || action == "down") {
        if (!menu)
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
            tetroFactory = LevelData(difficulty, path, seed); //make new factory for blocks
        }
    }
    else if (action == "leveldown") {
        if (difficulty != 0 && !menu) {
            difficulty--;
            tetroFactory = LevelData(difficulty, path, seed); //make new factory for blocks
        }
    }
    else if (action == "random") {
        if (difficulty == 3 || difficulty == 4 && !menu) {
            tetroFactory = LevelData(difficulty); //remake factory guarenteed random
        }
    }
    else if (action == "norandom") {
        if (difficulty == 3 || difficulty == 4 && !menu) {
            tetroFactory = LevelData(difficulty, newPath); //remake factory with path to sequence
        }
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
    }
    else if (action == "forceI") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "I";
        }
    }
    else if (action == "forceZ") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "Z";
        }
    }
    else if (action == "forceT") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "T";
        }
    }
    else if (action == "forceO") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "O";
        }
    }
    else if (action == "forceS") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "S";
        }
    }
    else if (action == "forceJ") {
        if (menu) { //if currently prompting user to choose effect
            currPunish = "J";
        }
    }
    else { //the remaining commands will be to force own block
        if (!menu) {
            sufferPunishment(action);
            notifyObservers();
        }
    }
}

void Board::sufferPunishment(string effect) {
    if (effect == "blind")
        isBlind = true;
    else if (effect == "I") {
        currTetro = tetroFactory.forceGenerate("I"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr { *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "J") {
        currTetro = tetroFactory.forceGenerate("J"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "L") {
        currTetro = tetroFactory.forceGenerate("L"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "O") {
        currTetro = tetroFactory.forceGenerate("O"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "S") {
        currTetro = tetroFactory.forceGenerate("S"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "Z") {
        currTetro = tetroFactory.forceGenerate("Z"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "T") {
        currTetro = tetroFactory.forceGenerate("T"); //make a specific tetro as current
        unique_ptr<Tetromino> forcedPtr{ *currTetro }; //make it a unique ptr
        observers.pop_back(); //delete previous current in observers and tetrominoes
        tetrominoes.pop_back();
        observers.emplace_back(forcedPtr); //replace with new current in both observers and tetrominoes
        tetrominoes.emplace_back(currTetro);
    }
    else if (effect == "*") {
        //currTetro does not change, this is a strict add-on

        Tetromino *specialTetro = tetroFactory.forceGenerate("*"); //make a specific tetro *
        unique_ptr<Tetromino> starPtr{ *specialTetro }; //make it a unique ptr

        //nothing is popped off since this is a strict addition

        observers.emplace_back(starPtr); //add starTetromino to observers (award potential points), not added to tetrominoes since it cannot be forced
        starPtr->drop(); //this immediately drops the starBlock
    }
    else if (effect == "heavy")
        currTetro->toggleHeavy();
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
            if (castedInfo->previously.size() == 0) { //newly instantiated
                if (isGameOver(*castedInfo)) {
                    hasLost = true;
                    notifyObservers(); //display ending screen
                }
            }
            else { //a move done to an existing nondropped tetromino
                for (int i = 0; i < castedInfo->absCoords.size(); i++) {
                    grid[castedInfo->previously[i][1]][castedInfo->previously[i][0]] = ' '; //fill old location
                    grid[castedInfo->absCoords[i][1]][castedInfo->absCoords[i][0]] = castedInfo->type; //new location
                }
                if (checkDropped(*castedInfo)) //check if the tetromino has dropped to the bottom
                    clearLine(); //complete end of turn actions, add points clear lines etc.
            }
        }
    }
    else { //if caller is opponent board, only case is to suffer effect
        BoardInfo *castedBInfo = static_cast<BoardInfo *>(info);
        if (!castedBInfo->isTurn)
            isTurn = true;
        sufferPunishment(castedBInfo->punishType);
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
    unique_ptr<BoardInfo> bInfo { new BoardInfo(displayGrid, currPunish, playerID, deletedRow, nextTetro.get(), isTurn, menu, hasLost, "board") };
    return bInfo;
}