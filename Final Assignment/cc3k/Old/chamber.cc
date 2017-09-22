#include "chamber.h"

using namespace std;

Chamber::Chamber (const int x, const int y, std::vector<vector<char> > & board, const int chamberID) {
    floodFill (x, y, board, chamberID);
    srand (time(NULL));
}

void Chamber::floodFill (const int x, const int y,  std::vector<vector<char> > & board, const int chamberID) {
    board.at(x).at(y) = chamberID + '0';
    addFloorPoint (x, y);
    if (board.at(x+1).at(y) == '.')
        floodFill (x + 1, y, board, chamberID);
    if (board.at(x-1).at(y) == '.')
        floodFill (x - 1, y, board, chamberID);
    if (board.at(x).at(y+1) == '.')
        floodFill (x, y + 1, board, chamberID);
    if (board.at(x).at(y-1) == '.')
        floodFill (x, y-1, board, chamberID);
}

void Chamber::addFloorPoint(const int x, const int y) {
    pair <int, int> mypair;
    mypair = make_pair (x, y);
    chamberPoints.push_back (mypair);
}

bool Chamber::isInChamber(const int x, const int y) {
    for (unsigned int i = 0; i < chamberPoints.size(); i++) {
        if (chamberPoints[i].first == x && chamberPoints[i].second == y) {
            return true;
        }
    }
    return false;
}

std::pair<int, int>Chamber::getRandomLoc() {
    int randomLoc;
    randomLoc = rand() % chamberPoints.size();
    std::pair<int, int> randomPoint;
    randomPoint = chamberPoints.at(randomLoc);

    return randomPoint;
}
