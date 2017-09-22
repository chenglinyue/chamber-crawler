#include "caption.h"
#include <iomanip>
using namespace std;

Caption::Caption() : gold(0), stage(1) {}

void Caption::updateCaption() {
    cout << "Race: " << race << setw(67) << "Floor: " << stage << endl;
    cout << "Gold: " << gold << endl;
    cout << "HP: " << hp << endl;
    cout << "Atk: " << atk << endl;
    cout << "Def: " << def << endl;
    cout << "Action: " << action << endl;
}

void Caption::setAction(string actionString) {
    action = actionString;
}

void Caption::setRace(string raceString) {
    race = raceString;
}

string Caption::getAction() {
    return action;
}

void Caption::setHP(int health) {
    hp = health;
}

void Caption::setAtk(int attack) {
    atk = attack;
}

void Caption::setDef(int defence) {
    def = defence;
}

void Caption::setStage(int stageNumber) {
    stage = stageNumber;
}

void Caption::setGold(int amount) {
    gold = amount;
}

int Caption::getGold() {
    return gold;
}
