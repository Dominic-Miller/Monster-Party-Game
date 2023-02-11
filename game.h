#include <iostream>
using namespace std;

class Monster {
    friend ostream& operator<<(ostream&, const Monster&);

    public:
        Monster(); //Default constructor
        int GetMonsterPower() const;
        int GetMonsterHealth() const;
        void SetMonsterHealth(int);

    private:
        int MonsterHealth; //Health of monster
        int MonsterPower; //Power of monster

};

class MonsterParty {

    public:
        MonsterParty(); //Default Constructor
        MonsterParty(const MonsterParty&); //Deep copy constructor
        void operator=(const MonsterParty&); //Deep copy assignment
        ~MonsterParty();

        void SetMonsterPartyXCoord(int);
        void SetMonsterPartyYCoord(int);
        int GetCurrentSize() const;
        Monster* GetMonsterPartyList() const;
        void SetCurrentSize(int);
        void SetMonsterPartyList(MonsterParty);
        int GetMonsterPartyReward() const;
        void UpdateMonsterHealth(int, int);
        void SetAliveSize(int);
        int GetAliveSize() const;

    private:
        int xCoord;
        int yCoord;
        Monster* MonsterPartyList; //List of monsters in the party
        int aliveSize;
        int currentSize;
        int MonsterPartyReward;


};
class Character {
    friend ostream& operator<<(ostream&, const Character&);

    public:
        Character(); //Default constructor
        int GetCharacterHealth() const;
        int GetCharacterPower() const;
        void SetCharacterHealth(int);

    private:
        int CharacterHealth; //Health of character
        int CharacterPower; //Power of character

};

class Party {

    public:
        Party(); //Default constructor
        Party(const Party&); //Deep copy constructor
        void operator=(const Party&); //Deep copy assignment
        void MoveParty(char);
        char Combat(MonsterParty);
        void CollectTreasure();
        void Trap();
        ~Party();

        void SetPartyXCoord(int);
        void SetPartyYCoord(int);
        void SetTreasureCounter(int);
        int GetTreasureCounter() const;

    private:
        int xCoord;
        int yCoord;
        int TreasureCounter; //Treasure counter
        Character* PartyList; //List of characters in the party
        int currentSize;

};

