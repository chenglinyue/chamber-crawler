#include "caption.h"
#include <iomanip>
using namespace std;

Caption::Caption() : gold(0), stage(1) {}

// Prints current state of game
void Caption::updateCaption() {
    cout << "Race: " << race << setw(67) << "Floor: " << stage << endl;
    cout << "Gold: " << gold << endl;
    cout << "HP: " << hp << endl;
    cout << "Atk: " << atk << endl;
    cout << "Def: " << def << endl;
    cout << "Action: " << action << endl;
}

// setter for action field
void Caption::setAction(string actionString) {
    action = actionString;
}
// setter for race field
void Caption::setRace(string raceString) {
    race = raceString;
}

// getter for action field
string Caption::getAction() {
    return action;
}

// setter for hp field
void Caption::setHP(int health) {
    hp = health;
}

// setter for atk field
void Caption::setAtk(int attack) {
    atk = attack;
}

// setter for def field
void Caption::setDef(int defence) {
    def = defence;
}

// setter for stage field
void Caption::setStage(int stageNumber) {
    stage = stageNumber;
}

// setter for gold field
void Caption::setGold(int amount) {
    gold = amount;
}

// getter for gold field
int Caption::getGold() {
    return gold;
}
