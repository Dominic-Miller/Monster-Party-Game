#include "game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//Monster Class
ostream& operator<<(ostream& o, const Monster& m) {
    o << "Health: " << m.MonsterHealth << " - Power: " << m.MonsterPower;
    return o;
}

Monster::Monster() { //Default constructor
    MonsterHealth = (rand() % 21) + 15;
    MonsterPower = (rand() % 6) + 1;
}

int Monster::GetMonsterHealth() const {
    return MonsterHealth;
}

int Monster::GetMonsterPower() const {
    return MonsterPower;
}

void Monster::SetMonsterHealth(int hp) {
    MonsterHealth = hp;
}





//MonsterPartyClass
MonsterParty::MonsterParty() { //Default Constructor
    currentSize = (rand() % 5) + 1; //Random amount of monsters in party between 1 and 5
    aliveSize = currentSize;
    MonsterPartyReward = currentSize * 5; //5 Gold per Monster
    MonsterPartyList = new Monster[currentSize];
    for (int i = 0; i < currentSize; i++) {
        MonsterPartyList[i] = Monster(); //Adds default Monster to each index of the party
    }
}

MonsterParty::MonsterParty(const MonsterParty& m) { //Deep copy constructor
    currentSize = m.currentSize;
    aliveSize = m.aliveSize;
    MonsterPartyReward = m.MonsterPartyReward;
    MonsterPartyList = new Monster[currentSize];
    for (int i = 0; i < currentSize; i++) {
        MonsterPartyList[i] = m.MonsterPartyList[i];
    }
}

void MonsterParty::operator=(const MonsterParty& m) { //Deep copy assignment
    currentSize = m.currentSize;
    aliveSize = m.aliveSize;
    MonsterPartyReward = m.MonsterPartyReward;
    delete [] MonsterPartyList;
    MonsterPartyList = new Monster[currentSize];
    for (int i = 0; i < currentSize; i++) {
        MonsterPartyList[i] = m.MonsterPartyList[i];
    }
}

MonsterParty::~MonsterParty() {
    delete [] MonsterPartyList;
}

void MonsterParty::SetMonsterPartyXCoord(int x) {
    xCoord = x;
}

void MonsterParty::SetMonsterPartyYCoord(int y) {
    yCoord = y;
}

int MonsterParty::GetCurrentSize() const {
    return currentSize;
}

Monster* MonsterParty::GetMonsterPartyList() const {
    return MonsterPartyList;
}

void MonsterParty::SetCurrentSize(int s) {
    currentSize = s;
}

int MonsterParty::GetMonsterPartyReward() const {
    return MonsterPartyReward;
}

void MonsterParty::UpdateMonsterHealth(int index, int health) {
    MonsterPartyList[index].SetMonsterHealth(health);
}

void MonsterParty::SetAliveSize(int s) {
    aliveSize = s;
}

int MonsterParty::GetAliveSize() const {
    return aliveSize;
}





//Character Class
ostream& operator<<(ostream& o, const Character& c) {
    o << "Health: " << c.CharacterHealth << " - Power: " << c.CharacterPower;
    return o;
}

Character::Character() { //Default constructor
    CharacterHealth = (rand() % 21) + 80;
    CharacterPower = (rand() % 7) + 4;
}

int Character::GetCharacterHealth() const {
    return CharacterHealth;
}

int Character::GetCharacterPower() const {
    return CharacterPower;
}

void Character::SetCharacterHealth(int hp) {
    if (hp > 0) {
        CharacterHealth = hp;
    }
    else {
        CharacterHealth = 0;
    }
}





//Party Class
Party::Party() { //Default constructor
    currentSize = 5;
    PartyList = new Character[5];
    for (int i = 0; i < 5; i++) {
        PartyList[i] = Character(); //Adds default character to each index of the party
    }
}

Party::Party(const Party& p) { //Deep copy constructor
    currentSize = p.currentSize;
    PartyList = new Character[currentSize];
    for (int i = 0; i < currentSize; i++) {
        PartyList[i] = p.PartyList[i];
    }
}

void Party::operator=(const Party& p) { //Deep copy assignment
    currentSize = p.currentSize;
    delete [] PartyList;
    PartyList = new Character[currentSize];
    for (int i = 0; i < currentSize; i++) {
        PartyList[i] = p.PartyList[i];
    }
}

void Party::MoveParty(char d) {
    if(d != 'w' && d != 'W' && d != 'd' && d != 'D' && d != 's' && d != 'S' && d != 'a' && d != 'A') {
        return;
    }
    else if(d == 'w' || d == 'W') {
        yCoord++;
    } 
    else if(d == 'd' || d == 'D') {
        xCoord++;
    } 
    else if(d == 's' || d == 'S') {
        yCoord--;
    } 
    else if(d == 'a' || d == 'A') {
        yCoord++;
    }
}

char Party::Combat(MonsterParty MP) {
    int counter = 0;
    char input;
    int MonsterToAttack;
    int PlayerToAttack;
    int MonsterThatAttacks;
    bool canBreak = false;
    int NewHealth;
    int chance;
    int Miss;
    bool escape = false;
    cout << "You've encountered a party of Monsters!" << endl;
    while (MP.GetCurrentSize() > 0 || escape == false) {
        //Player's turn
        if (counter % 2 == 0) {
            cout << "\nIt's your turn!" << endl;
            //Chance to escape
            cout << "Would you like to attempt an escape (Y or N)?: ";
            cin >> input;
            cout << endl;
            if (input == 'y' || input == 'Y') {
                chance = (rand() % 10) + 1;
                if (MP.GetCurrentSize() == 5) {
                    if (chance == 1) {
                        escape = true;
                        return 'E';
                    }
                }
                else if (MP.GetCurrentSize() == 4) {
                    if (chance == 1 || chance == 2) {
                        escape = true;
                        return 'E';
                    }
                }
                else if (MP.GetCurrentSize() == 3) {
                    if (chance == 1 || chance == 2 || chance == 3) {
                        escape = true;
                        return 'E';
                    }
                }
                else if (MP.GetCurrentSize() == 2) {
                    if (chance == 1 || chance == 2 || chance == 3 || chance == 4) {
                        escape = true;
                        return 'E';
                    }
                }
                else if (MP.GetCurrentSize() == 1) {
                    if (chance == 1 || chance == 2 || chance == 3 || chance == 4 || chance == 5) {
                        escape = true;
                        return 'E';
                    }
                }
                if (escape != true) {
                    cout << "Escape Failed!" << endl;
                }
            }

            //Attack a monster
            else {
                NewHealth = 10;
                for (int i = 0; i < currentSize; i++) {
                    for (int j = 0; j < MP.GetCurrentSize(); j++) {
                        if (MP.GetMonsterPartyList()[j].GetMonsterHealth() > 0) {
                            cout << "Monster " << j + 1 << " -> " << MP.GetMonsterPartyList()[j] << endl;
                        }
                        else {
                            cout << "Monster " << j + 1 << " -> " << "Dead" << endl;
                        }
                    }
                    cout << "Character " << i + 1 << " -> " << PartyList[i] << endl;
                    cout << "Which Monster would you like to attack with Character " << i + 1 << ": ";
                    cin >> MonsterToAttack;
                    cout << endl;
                    if (MP.GetMonsterPartyList()[MonsterToAttack - 1].GetMonsterHealth() <= 0) {
                        cout << "This Monster is already dead!" << endl;
                        i--;
                        continue;
                    }
                    //15% chance to miss
                    Miss = (rand() % 20) + 1;
                    if (Miss == 1 || Miss == 2 || Miss == 3) {
                        cout << "Oh no! Your Attack Missed!" << endl << endl;
                        continue;
                    }
                    //If attack hits
                    if (MonsterToAttack <= MP.GetCurrentSize() && MonsterToAttack > 0) {
                        NewHealth = (MP.GetMonsterPartyList()[MonsterToAttack - 1].GetMonsterHealth()) - PartyList[i].GetCharacterPower();
                        MP.UpdateMonsterHealth(MonsterToAttack - 1, NewHealth);
                        cout << "You dealt " << PartyList[i].GetCharacterPower() << " damage to Monster " << MonsterToAttack << "!\n\n";
                    }
                    else {
                        cout << "Invalid Monster!" << endl;
                        i--;
                        continue;
                    }
                    //If Monster is killed
                    if (NewHealth <= 0) {
                        MP.SetAliveSize(MP.GetAliveSize() - 1);
                        cout << "A Monster has fallen!" << endl << endl;
                    }
                    //If all monsters are killed
                    if (MP.GetAliveSize() < 1) {
                        return 'W';
                    }
                }

            }
        }

        //Monster's turn
        else {
            cout << "\nIt's the Monster Party's turn!" << endl;
            //50% Chance the attack hits
            int Valid = (rand() % 2);
            if (Valid == 0) {
                cout << "The Monster's Attack Missed!" << endl;
            }
            else {
                canBreak = false;
                //Need random number between 0 and size of player party -1
                PlayerToAttack = (rand() % currentSize) + 1;
                while (canBreak == false) {
                    MonsterThatAttacks = (rand() % MP.GetCurrentSize());
                    if (MP.GetMonsterPartyList()[MonsterThatAttacks].GetMonsterHealth() <= 0) {
                        continue;
                    }
                    else {
                        canBreak = true;
                    }
                }
                NewHealth = PartyList[PlayerToAttack - 1].GetCharacterHealth() - MP.GetMonsterPartyList()[MonsterThatAttacks].GetMonsterPower(); //Assuming you defeat the monsters one at a time
                PartyList[PlayerToAttack - 1].SetCharacterHealth(NewHealth);
                cout << "Ouch! The Monster has his Character " << PlayerToAttack << "! New Health: " << NewHealth << endl;
                //If character is killed, resize the array
                if (PartyList[PlayerToAttack].GetCharacterHealth() <= 0) {
                    Character* tmp = new Character[currentSize - 1];
                    for (int x = 0; x < currentSize; x++) {
                        tmp[x] = PartyList[x];
                    }
                    delete [] PartyList;
                    PartyList = tmp;
                    delete [] tmp;
                    cout << "A Player has fallen!" << endl;
                }
            }
        }
        counter++;
    }

    if (currentSize == 0) {
        return 'L';
        //Game Over
    }

}

void Party::CollectTreasure() {
    int amount = (rand() % 10) + 1;
    TreasureCounter += amount;
    cout << "You've found some treasure! You now have " << TreasureCounter << " Gold!\n";
}

void Party::Trap() {
    int winOrloss = (rand() % 100);
    if (winOrloss >= 50) {
        int amountWon = (rand() % 11);
        TreasureCounter += amountWon;
        cout << "You got lucky stepping on this trap! You found " << amountWon << " Gold!" << endl << endl;
    }
    else {
        int damageTaken = (rand() % 11);
        for (int o = 0; o < currentSize; o++) {
            PartyList[o].SetCharacterHealth(PartyList[o].GetCharacterHealth() - damageTaken);
            if (PartyList[o].GetCharacterHealth() <= 0) {
                    Character* tmp = new Character[currentSize - 1];
                    for (int x = 0; x < currentSize; x++) {
                        tmp[x] = PartyList[x];
                    }
                    delete [] PartyList;
                    PartyList = tmp;
                    delete [] tmp;
                    cout << "A Player has fallen!" << endl;
                }
        }
        cout << "Ouch! You shouldn't have fell for the trap! All party members took " << damageTaken << " damage." << endl << endl;
    }
}

Party::~Party() {
    delete [] PartyList;
}

void Party::SetPartyXCoord(int x) {
    xCoord = x;
}

void Party::SetPartyYCoord(int y) {
    yCoord = y;
}

void Party::SetTreasureCounter(int x) {
    TreasureCounter = x;
}

int Party::GetTreasureCounter() const {
    return TreasureCounter;
}


