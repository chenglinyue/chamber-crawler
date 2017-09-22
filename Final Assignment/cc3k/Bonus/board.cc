#include "board.h"
#include "caption.h"

using namespace std;

Board::Board() {
    caption = new Caption;
}

Board::~Board() {
    delete caption;
}

void Board::update() {

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

void Board::setHP(const int health) {
    caption->setHP(health);
}

void Board::setAtk(const int attack) {
    caption->setAtk(attack);
}

void Board::setDef(const int defence) {
    caption->setDef(defence);
}

void Board::setGold(const int amount) {
    caption->setGold(amount);
}

void Board::setRace(const string race) {
    caption->setRace(race);
}

void Board::setStage(const int stageNumber) {
    caption->setStage(stageNumber);
}

int Board::getGold() {
    return caption->getGold();
}

void Board::setBoard(std::vector <std::vector<char> > &theBoard){
    board = theBoard;
}

char Board::getTile(pair<int, int> loc){
    return board.at(loc.first).at(loc.second);
}

void Board::setTile(const pair<int, int> loc, const char c) {
    board.at(loc.first).at(loc.second) = c;
}
