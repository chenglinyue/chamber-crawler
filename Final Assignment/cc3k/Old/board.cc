#include "board.h"
#include "caption.h"

using namespace std;

Board::Board() {
    caption = new Caption;
}

Board::~Board() {
    delete caption;
}

void Board::update(std::vector <std::vector<char> > board) {

    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j< board.at(i).size(); j ++) {
            cout << board.at(i).at(j);
        }
        cout << endl;
    }
    caption->updateCaption();
}

void Board::setAction (string action) {
    caption->setAction(action);
}

string Board::getAction() {
    return caption->getAction();
}

void Board::setHP(int health) {
    caption->setHP(health);
}

void Board::setAtk(int attack) {
    caption->setAtk(attack);
}

void Board::setDef(int defence) {
    caption->setDef(defence);
}

void Board::setGold(int amount) {
    caption->setGold(amount);
}

void Board::setRace(string race) {
    caption->setRace(race);
}

void Board::setStage(int stageNumber) {
    caption->setStage(stageNumber);
}

int Board::getGold() {
    return caption->getGold();
}
