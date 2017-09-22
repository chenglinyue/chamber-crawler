
#include "board.h"
using namespace std;

Board::Board() {
    // Height of 2D board is 27
    board = new pair<char,char>*[BOARDHEIGHT];
    for (int i = 0; i < BOARDHEIGHT; i++) {
        board[i] = new pair<char,char>[BOARDWIDTH];
        for (int j = 0; j< BOARDWIDTH; j ++) {
            board[i][j].first = ' ';
            board[i][j].second = ' ';
        }
    }

    // Initialize chambers
    chambers[0] = new Chamber(CHAMBERONEX, CHAMBERONEY, CHAMBERONEWIDTH, CHAMBERONEHEIGHT);
    chambers[1] = new Chamber(CHAMBERTWOX, CHAMBERTWOY, CHAMBERTWOWIDTH, CHAMBERTWOHEIGHT);
    chambers[2] = new Chamber(CHAMBERTHREEX, CHAMBERTHREEY, CHAMBERTHREEWIDTH, CHAMBERTHREEHEIGHT);
}

void Board::initializeBoard() {
    // Initialize borders
    for (int i = 0; i < BOARDHEIGHT; i++) {
        // Left and right borders
        board[i][0].first = '|';
        board[i][BOARDWIDTH - 1].first = '|';
    }
    for (int j = 1; j < BOARDWIDTH - 1; j++) {
        // Top and bottom borders
        board[0][j].first = '-';
        board[BOARDHEIGHT - 1][j].first = '-';
    }

    // Initialize chambers
    for (int chamberNumber = 0; chamberNumber < NUMCHAMBERS; chamberNumber++) {
        // Initialize borders of chambers
        for (int i = chambers[chamberNumber]->y;
                 i < chambers[chamberNumber]->y + chambers[chamberNumber]->height; i++) {
            // Left and right
            board[i][chambers[chamberNumber]->x].first = '|';
            board[i][chambers[chamberNumber]->x + chambers[chamberNumber]->width - 1].first = '|';
        }

        for (int i = chambers[chamberNumber]->x + 1;
                 i < chambers[chamberNumber]->x + chambers[chamberNumber]->width - 1; i++) {
            // Top and bottom
            board[chambers[chamberNumber]->y][i].first = '-';
            board[chambers[chamberNumber]->y + chambers[chamberNumber]->height - 1][i].first = '-';
        }

        for (int i = chambers[chamberNumber]->y + 1;
                 i < chambers[chamberNumber]->y + chambers[chamberNumber]->height - 1; i++) {
            for (int j = chambers[chamberNumber]->x+ 1;
                j < chambers[chamberNumber]->x + chambers[chamberNumber]->width - 1; j++) {
                    board[i][j].first = '.';
                    char chamber = (chamberNumber+1) + '0';
                    board[i][j].second = chamber;
            }
        }
    }
}

void Board::printBoard() {
    for (int i = 0; i < BOARDHEIGHT; i++) {
        for (int j = 0; j< BOARDWIDTH; j ++) {
            cout << board[i][j].first;
        }
        cout << endl;
    }
}
