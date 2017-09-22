#include "board.h"
#include "caption.h"

using namespace std;

Board::Board() {
    caption = new Caption;
}

Board::~Board() {
    delete caption;
}

void Board::update(pair <int, int> playerLoc, int sightRadius) {
    int x = playerLoc.second - sightRadius;
    int y = playerLoc.first - sightRadius;
    bool newLine = false;

    for (int i = y; i < y + sightRadius*2; i++) {
        newLine = false;
        for (int j = x; j < x + sightRadius*2; j++) {
            if (i >= 0 && j >= 0 && i < 25 && j < 79) {
                cout << board.at(i).at(j);
                newLine = true;
            }
        }
        if (newLine) cout << endl;
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
