#include "board.h"
#include "game.h"
#include <iostream>
using namespace std;

int main() {

    //Check if party can move in the desired direction
    //Check if all players have died - the party loses
    //Win only if all monsters are defeated and treasure is picked up

    Board GameBoard(15);
    Party GameParty;
    bool active = true;
    char move;
    char output;
    char otherOutput;
    cout << "\nWelcome and Good Luck!" << endl;
    cout << "Move with W-A-S-D" << endl << endl;

    while (active == true) {
        cout << GameBoard;
        cout << "-> ";
        cin >> move;
        cout << endl;

        output = GameBoard.CheckMove(move);
        if(output != 'i') {
            GameParty.MoveParty(move);
            GameBoard.SetBoardState(move);
        }
        if (output == 't') {
            GameParty.CollectTreasure();
            GameBoard.RemoveVariable();
            GameBoard.SetRealNumTreasures(GameBoard.GetRealNumTreasures() - 1);
        }
        if (output == 'm') {
            MonsterParty enemy;
            otherOutput = GameParty.Combat(enemy);
            //Game Over
            if (otherOutput == 'L') {
                cout << "\nGame Over...\n";
                active = false;
                return 0;
            }
            //Beat all monsters
            else if (otherOutput == 'W') {
                cout << "You've defeated all the enemies! Congragulations" << endl;
                GameParty.SetTreasureCounter(GameParty.GetTreasureCounter() + enemy.GetMonsterPartyReward());
                cout << "You found some Gold while looting the Monsters! You now have " << GameParty.GetTreasureCounter() << " Gold!\n";
                GameBoard.SetRealNumMobs(GameBoard.GetRealNumMobs() - 1);
                GameBoard.RemoveVariable();
            }
            else if (otherOutput == 'E') {
                cout << "Whew! That was a close one! You've escaped the monsters." << endl;
                //Put 'M' in another spot on the board
                GameBoard.NewMob();
            }

        }
        if (output == 'r') {
            GameParty.Trap();
            GameBoard.RemoveVariable();
        }
        if (output == 'i') {
            cout << "Invalid move!" << endl;
        }
        cout << "\nNumber of mobs remaining: " << GameBoard.GetRealNumMobs() << " - Number of treasures remaining: " <<GameBoard.GetRealNumTreasures() << endl << endl;
        //Win
        if (GameBoard.GetRealNumMobs() <= 0 && GameBoard.GetRealNumTreasures() <= 0) {
            cout << "\n*******************************************" << endl;
            cout << "Congragulations, you have won!" << endl;
            cout << "Created by: Dominic Miller" << endl;
            cout << "*******************************************" << endl;
            active = false;
            return 0;
        }

    }

    return 0;
}