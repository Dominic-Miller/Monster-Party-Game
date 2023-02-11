#include <iostream>
using namespace std;

class Board {
    friend ostream& operator<<(ostream&, const Board&);

    public:
        Board(int _size);
        void SetBoardState(char);
        char CheckMove(char);
        void RemoveVariable();
        void NewMob();
        void SetRealNumMobs(int);
        void SetRealNumTreasures(int);
        int GetRealNumTreasures() const;
        int GetRealNumMobs() const;
        ~Board();

    private:
        //data
        const int maxTreasures;
        int numTreasures;
        const int maxMobs;
        int numMobs;
        const int maxTraps;
        int numTraps;
        int size;
        char** boardState;
        int** treasures;
        int** mobs;
        int** traps;
        //entrance
        int x_enter;
        int y_enter;
        //exit
        int x_exit;
        int y_exit;
        //functionality
        void setupEntrance();
        void setupTreasure();
        void setupMobs();
        void setupTraps();

        int xCoord;
        int yCoord;

        int realNumMobs;
        int realNumTreasure;

};
