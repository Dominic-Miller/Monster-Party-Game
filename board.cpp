#include "board.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Board::Board(int _size=10):maxTreasures(_size/2),maxMobs(_size),maxTraps(_size/2) {
    size = _size;
    //allocate a new board
    boardState = new char*[size];
    for(int i = 0; i < size; i++) {
        boardState[i] = new char[size];
        for(int j = 0; j < size; j++) {
            if(i == 0 || i == size-1) {
                boardState[i][j]= '-';
                continue;
            } 
            else if (j == 0 || j == size-1) {
                boardState[i][j] = '|';
                continue;
            }
        boardState[i][j] = ' ';
        }
    }
    //set the entrance
    setupEntrance();
    //set the treasures
    setupTreasure();
    //set the mobs
    setupMobs();
    //set the traps
    setupTraps();
}

void Board::SetBoardState(char d) {
    if (d == 'd' || d == 'D') {
        boardState[xCoord][yCoord+1] = 'X';
        boardState[xCoord][yCoord] = ' ';
        yCoord++;
    }
    else if (d == 's' || d == 'S') {
        boardState[xCoord+1][yCoord] = 'X';
        boardState[xCoord][yCoord] = ' ';
        xCoord++;
    }
    else if (d == 'a' || d == 'A') {
        boardState[xCoord][yCoord-1] = 'X';
        boardState[xCoord][yCoord] = ' ';
        yCoord--;
    }
    else if (d == 'w' || d == 'W') {
        boardState[xCoord-1][yCoord] = 'X';
        boardState[xCoord][yCoord] = ' ';
        xCoord--;
    }
}

char Board::CheckMove(char d) {
    if (d == 'd' || d == 'D') {
        if (boardState[xCoord][yCoord+1] == 'M') {
            return 'm'; //Monster in this direction
        }
        if (boardState[xCoord][yCoord+1] == 'T') {
            return 't'; //Treasure in this direction
        }
        if (boardState[xCoord][yCoord+1] == 'R') {
            return 'r'; //Trap in this direction
        }
        if (boardState[xCoord][yCoord+1] == '|' || boardState[xCoord][yCoord+1] == '-') {
            return 'i'; //Invalid direction to move
        }
        else {
            return 'v'; //Valid direction to move
        }
    }
    else if (d == 's' || d == 'S') {
        if (boardState[xCoord+1][yCoord] == 'M') {
            return 'm';
        }
        if (boardState[xCoord+1][yCoord] == 'T') {
            return 't';
        }
        if (boardState[xCoord+1][yCoord] == 'R') {
            return 'r';
        }
        if (boardState[xCoord+1][yCoord] == '|' || boardState[xCoord+1][yCoord] == '-') {
            return 'i';
        }
        else {
            return 'v';
        }
    }
    else if (d == 'a' || d == 'A') {
        if (boardState[xCoord][yCoord-1] == 'M') {
            return 'm';
        }
        if (boardState[xCoord][yCoord-1] == 'T') {
            return 't';
        }
        if (boardState[xCoord][yCoord-1] == 'R') {
            return 'r';
        }
        if (boardState[xCoord][yCoord-1] == '|' || boardState[xCoord][yCoord-1] == '-') {
            return 'i';
        }
        else {
            return 'v';
        }
    }
    else if (d == 'w' || d == 'W') {
        if (boardState[xCoord-1][yCoord] == 'M') {
            return 'm';
        }
        if (boardState[xCoord-1][yCoord] == 'T') {
            return 't';
        }
        if (boardState[xCoord-1][yCoord] == 'R') {
            return 'r';
        }
        if (boardState[xCoord-1][yCoord] == '|' || boardState[xCoord-1][yCoord] == '-') {
            return 'i';
        }
        else {
            return 'v';
        }
    }
    else {
        return 'i';
    }
}

void Board::RemoveVariable() {
    boardState[xCoord][yCoord] = 'X';
}

void Board::NewMob() {
    bool valid = false;
    int row;
    int column;
    while (valid == false) {
        //get row
        row = rand()%(size-2) + 1;
        //get column
        column = rand()%(size-2) + 1;
        //place treasures
        if (boardState[row][column] == 'R' || boardState[row][column] == 'T') {
            continue;
        }
        else {
            valid = true;
        }
    }
    boardState[row][column] = 'M';
    mobs[0] = new int[2];
    mobs[0][0] = row;
    mobs[0][1] = column;
}

void Board::SetRealNumMobs(int x) {
    realNumMobs = x;
}

void Board::SetRealNumTreasures(int x) {
    realNumTreasure = x;
}

int Board::GetRealNumTreasures() const {
    return realNumTreasure;
}

int Board::GetRealNumMobs() const {
    return realNumMobs;
}

ostream& operator<<(ostream& s, const Board& db) {
    for(int i = 0; i < db.size; i++) {
        for(int j = 0; j < db.size; j++) {
            s << db.boardState[i][j] << "\t";
        }
        s << endl<<endl;
    }
    return s;
}

void Board::setupEntrance() {
    //find the entry
    srand(time(0));
    //pick a number 0-3 to figure out what wall the entrance will be on
    int wall = rand()%4;
    //pick a number 1-8 to figure out what position on that wall the entrance will be at (this keeps the door from being in a corner)
    int pos = rand()%(size-2) + 1;
    switch(wall) {
        case 0:
            boardState[pos][0] = 'X';
            boardState[pos-1][0] = '-';
            boardState[pos+1][0] = '-';
            xCoord = pos;
            yCoord = 0;
            break;
        case 1:
            boardState[0][pos] = 'X';
            boardState[0][pos-1] = '|';
            boardState[0][pos+1] = '|';
            xCoord = 0;
            yCoord = pos;
            break;
        case 2:
            boardState[pos][size-1] = 'X';
            boardState[pos-1][size-1] = '-';
            boardState[pos+1][size-1] = '-';
            xCoord = pos;
            yCoord = size - 1;
            break;
        case 3:
            boardState[size-1][pos] = 'X';
            boardState[size-1][pos-1] = '|';
            boardState[size-1][pos+1] = '|';
            xCoord = size - 1;
            yCoord = pos;
            break;
    }
}

void Board::setupTreasure() {
    realNumTreasure = 0;
    numTreasures = (rand() % 6) + 5;
    treasures = new int*[numTreasures];
    for(int i = 0; i < numTreasures; i++) {
        //get row
        int row = rand()%(size-2) + 1;
        //get column
        int column = rand()%(size-2) + 1;
        //place treasures
        boardState[row][column] = 'T';
        treasures[i] = new int[2];
        treasures[i][0] = row;
        treasures[i][1] = column;
        cout << "Allocated treasure " << i << endl; 
        realNumTreasure++;
    }
}

void Board::setupMobs() {
    realNumMobs = 0;
    numMobs = (rand() % 6) + 5;
    mobs = new int*[numMobs];
    for(int i = 0; i < numMobs; i++) {
        //get row
        int row = rand()%(size-2) + 1;
        //get column
        int column = rand()%(size-2) + 1;
        //place treasures
        if (boardState[row][column] == 'T') {
            i--;
            continue;
        }
        boardState[row][column] = 'M';
        mobs[i] = new int[2];
        mobs[i][0] = row;
        mobs[i][1] = column;
        cout << "Allocated mob " << i << endl;
        realNumMobs++;
    }
}

void Board::setupTraps() {
    numTraps = (rand() % 3) + 1;
    traps = new int*[numTraps];
    for(int i = 0; i < numTraps; i++) {
        //get row
        int row = rand()%(size-2) + 1;
        //get column
        int column = rand()%(size-2) + 1;
        //place treasures
        if (boardState[row][column] == 'R' || boardState[row][column] == 'T') {
            i--;
            continue;
        }
        boardState[row][column] = 'R';
        mobs[i] = new int[2];
        mobs[i][0] = row;
        mobs[i][1] = column;
        cout << "Allocated trap " << i << endl;
    }
}

Board::~Board() {
    cout << "Destroying game board state..." << endl;
    for(int i = 0; i < size; i++) {
        delete [] boardState[i];
    }
    delete [] boardState;
    cout << "Destroying mob state..." << endl;
    for(int i = 0; i < numMobs; i++) {
        cout << "Destroying mob " << i << endl;
        delete [] mobs[i];
    }   
    cout << "Destroying mob list..." << endl;
    delete [] mobs;
    cout << "Destroying treasure state..." << endl;
    for(int i = 0; i < numTreasures; i++) {
        cout << "Destroying treasure " << i << endl;
        delete [] treasures[i];
    }
    delete [] treasures;
    cout << "Destroying trap state..." << endl;
    for(int i = 0; i < numTraps; i++) {
        cout << "Destroying traps" << i << endl;
        delete [] traps[i];
    }
    delete [] traps;
}