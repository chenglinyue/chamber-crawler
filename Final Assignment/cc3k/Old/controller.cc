#include <math.h>
#include "controller.h"
#include "chamber.h"
#include "caption.h"
#include "halfling.h"
#include "orcs.h"
#include "board.h"
#include "item.h"
#include "drow.h"
#include "dragon.h"
#include "merchant.h"
#include "elf.h"
#include "dwarf.h"
#include "human.h"
#include "shade.h"
#include "troll.h"
#include "goblin.h"
#include "vampire.h"
#include "treasure.h"
#include "woundatk.h"
#include "wounddef.h"
#include "boostatk.h"
#include "boostdef.h"
#include "restorehealth.h"
#include "poisonhealth.h"
#include <cmath>
#include <iomanip>

using namespace std;

// 0 param Constructor
Controller::Controller():oldFloorTile('.'), setHostile(false), stageNumber(1), gameOver(false) {
    view = new Board;
    nameOfFile = "template_map.txt";
}

// 0 param Constructor
Controller::Controller(string fileName):oldFloorTile('.'), setHostile(false), stageNumber(1), gameOver(false) {
    view = new Board;
    nameOfFile = fileName;
}

// Destructor
Controller::~Controller() {
    // Delete enemies
    for (unsigned int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    // Delete items
    for (unsigned int i = 0; i<items.size(); i++) {
        delete items[i];
    }
    // Delete chambers
    for (unsigned int i = 0; i < chambers.size(); i++) {
        delete chambers[i];
    }
    delete view;
    delete player;
}

void Controller::chooseCharacterRace() {
    cout << "Welcome to Chamber Crawler." << endl;
    cout << "Choose your character race:" << endl;
    cout << "s: Shade" << endl;
    cout << "d: Drow" << endl;
    cout << "v: Vampire" << endl;
    cout << "g: Goblin" << endl;
    cout << "t: Troll" << endl;
    string characterRace;
    cin >> characterRace;
    race = characterRace;
    if (race == "d") {
        player = new Drow(*this, make_pair (0,0), '@');
        view->setRace("Drow");
    } else if (race == "v") {
        player = new Vampire(*this, make_pair (0,0), '@');
        view->setRace("Vampire");
    } else if (race == "g") {
        player = new Goblin(*this, make_pair (0,0), '@');
        view->setRace("Goblin");
    } else if (race == "t") {
        player = new Troll(*this, make_pair (0,0), '@');
        view->setRace("Troll");
    } else {
        // Shade is the default race
        player = new Shade(*this, make_pair (0,0), '@');
        view->setRace("Shade");
        race = "s";
    }
}

void Controller::initializeControllerRandom() {
    isRandomlyGeneratedMap = true;
    if (stageNumber == 1)
        chooseCharacterRace();
    generateRandomItemLocations();
    // if a player attacked a merchant on a previous floor, turn all merchants hostile
    if (setHostile) turnMerchantsHostile();
    updateBoard();
    playGame();
}

void Controller::initializeControllerNotRandom() {
    isRandomlyGeneratedMap = false;
    ifstream mapFileStream(nameOfFile.c_str());

    if (stageNumber == 1) {
        chooseCharacterRace();
    }

    string mapLine;
    // Throw away unneeded lines
    for (int i = 0; i < 25 * (stageNumber - 1); i++) {
        getline (mapFileStream, mapLine);
    }
    for (int i = 0; i < 25; i++) {
        vector<char> line;
        vector<char> tempLine;

        getline (mapFileStream, mapLine);
        if (mapFileStream.eof())
            break;
        for (unsigned int i = 0; i < mapLine.length(); i++) {
            line.push_back (mapLine[i]);
            tempLine.push_back (mapLine[i]);
        }
        board.push_back (line);
        tempBoard.push_back (tempLine);
    }

    Item* genericItemList [10] = {  new RestoreHealth (*this, 'P'),
                                    new BoostAtk (*this, 'P'),
                                    new BoostDef (*this, 'P'),
                                    new PoisonHealth (*this, 'P'),
                                    new WoundAtk (*this, 'P'),
                                    new WoundDef (*this, 'P'),
                                    new Treasure (*this, 2, 'G'),
                                    new Treasure (*this, 1, 'G'),
                                    new Treasure (*this, 4, 'G'),
                                    new Treasure (*this, 6, 'G')};

    Enemy* genericEnemiesList [7] = { new Human (*this, make_pair (0,0), 'H'),
                                      new Halfling (*this, make_pair (0,0), 'L'),
                                      new Dragon (*this, make_pair (0,0), 'D'),
                                      new Orcs (*this, make_pair (0,0), 'O'),
                                      new Dwarf (*this, make_pair (0,0), 'W'),
                                      new Merchant (*this, make_pair (0,0), 'M'),
                                      new Elf (*this, make_pair (0,0), 'E')};

    for (unsigned int i = 0; i < tempBoard.size(); i++) {
        for (unsigned int j = 0; j < tempBoard.at(i).size(); j++) {
            // Set up all Items (treasure and potions)
            if ((tempBoard.at(i).at(j)) >= '0' && (tempBoard.at(i).at(j)) <= '9') {
                Item* tempItem = genericItemList[tempBoard.at(i).at(j)-'0']->copy();
                tempItem->setItemLoc (i, j);
                items.push_back (tempItem);

                // Set potions to P on board and Treasure to G
                board.at(i).at(j) = tempItem->getItemID();
            }
            // Set up player location
            if (tempBoard.at(i).at(j) == '@') {
                player->setCharacterLoc(i, j);
            }
            // Set up all enemies
            if ((tempBoard.at(i).at(j) >= 'A') && (tempBoard.at(i).at(j) <= 'Z')) {
                for (int k = 0; k < 7; k++) {
                    if (genericEnemiesList[k]->getCharacterID() == (tempBoard.at(i).at(j))) {
                        Character* tempEnemy = genericEnemiesList[k]->copy();
                        tempEnemy->setCharacterLoc (i, j);
                        enemies.push_back (dynamic_cast<Enemy *>(tempEnemy));
                        break;
                    }
                }
            }
        }
    }

    for (unsigned int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getCharacterID() == 'D') {
            // Link Dragon with it's dragon hoard
            for (unsigned int j = 0; j < items.size(); j++) {
                if (items[j]->getItemID() == 'G' && dynamic_cast<Treasure *>(items[j])->getAmount() == 6) {
                    int distance = sqrt((enemies[i]->getCharacterLoc().first - items[j]->getItemLoc().first) *
                                        (enemies[i]->getCharacterLoc().first - items[j]->getItemLoc().first) +
                                        (enemies[i]->getCharacterLoc().second - items[j]->getItemLoc().second) *
                                        (enemies[i]->getCharacterLoc().second - items[j]->getItemLoc().second));
                    if (distance <= sqrt(2)) {
                        dynamic_cast<Dragon *>(enemies[i])->setDragonHoard(*(dynamic_cast<Treasure *>(items[j])));
                        break;
                    }
                }
            }
        }
    }

    // Free up memory in the 'temporary' array of generic items and enemies
    for (int i = 0; i < 10; i++) {
        delete genericItemList[i];
    }

    for (int i = 0; i < 7; i++) {
        delete genericEnemiesList[i];
    }

    updateBoard();
    // if a player attacked a merchant on a previous floor, turn all merchants hostile
    if (setHostile) turnMerchantsHostile();
    playGame();
}

void Controller::playGame() {
    //updateBoard();
    endTurn = false;
    string command;
    while (!gameOver && cin >> command) {
        isValidCommand = false;
        player->makeMove();
        pair <int, int> playerLoc = player->getCharacterLoc();
        if (command == "q") {
            cout << "quitting..." << endl;
            return;
        } else if (command == "r") {
            restart();
            return;
        }
        else if (command == "ea") {
            moveCharacter(*player, 1, 0);
            if (isValidCommand) setAction("PC moves east. ");
        } else if (command == "we") {
            moveCharacter(*player, -1, 0);
            if (isValidCommand) setAction("PC moves west. ");
        } else if (command == "no") {
            moveCharacter(*player, 0, -1);
            if (isValidCommand) setAction("PC moves north. ");
        } else if (command == "so") {
            moveCharacter(*player, 0, 1);
            if (isValidCommand) setAction("PC moves south. ");
        } else if (command == "se") {
            moveCharacter(*player, 1, 1);
            if (isValidCommand) setAction("PC moves southeast. ");
        } else if (command == "sw") {
            moveCharacter(*player, -1, 1);
            if (isValidCommand) setAction("PC moves southwest. ");
        } else if (command == "ne") {
            moveCharacter(*player, 1, -1);
            if (isValidCommand) setAction("PC moves northeast. ");
        } else if (command == "nw") {
            moveCharacter(*player, -1, -1);
            if (isValidCommand) setAction("PC moves northwest. ");
        }

        if (endTurn) return;
        if (command == "a" || command == "u") {
            // Attacking
            string direction;
            cin >> direction;
            pair<int, int> objectLoc;
            bool isValidDirection = true;
            if (direction == "ea") {
                objectLoc = make_pair(playerLoc.first, playerLoc.second + 1);
            } else if (direction == "we") {
                objectLoc = make_pair(playerLoc.first, playerLoc.second - 1);
            } else if (direction == "no") {
                objectLoc = make_pair(playerLoc.first - 1, playerLoc.second);
            } else if (direction == "so") {
                objectLoc = make_pair(playerLoc.first + 1, playerLoc.second);
            } else if (direction == "se") {
                objectLoc = make_pair(playerLoc.first + 1, playerLoc.second + 1);
            } else if (direction == "sw") {
                objectLoc = make_pair(playerLoc.first + 1, playerLoc.second - 1);
            } else if (direction == "ne") {
                objectLoc = make_pair(playerLoc.first - 1, playerLoc.second + 1);
            } else if (direction == "nw") {
                objectLoc = make_pair(playerLoc.first - 1, playerLoc.second - 1);
            } else {
                isValidDirection = false;
            }
            if (isValidDirection) {
                // Attacking
                if (command == "a") {
                    for (unsigned int i = 0; i < enemies.size(); i++) {
                        if (enemies[i]->getCharacterLoc() == objectLoc) {
                            enemies[i]->attackedBy(*player);
                            isValidCommand = true;
                            break;
                        }
                    }
                } else if (command == "u") {
                    for (unsigned int i = 0; i < items.size(); i++) {
                        // Check if the item is a potion (i.e., not a treasure)
                        if (dynamic_cast<Treasure *>(items[i])) {
                            // Do nothing
                        } else {
                            if (items[i]->getItemLoc()== objectLoc) {
                                items[i]->pickUp(*player);
                                isValidCommand = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (gameOver) return; // Game might have ended after player's turn
        if (!isValidCommand) continue;// enemies don't move or attack if player entered an invalid command
        else if (isValidCommand && race == "t") dynamic_cast<Troll *>(player)->recover();

        // Move enemies randomly or attack player if beside them
        for (unsigned int i = 0; i < enemies.size(); i++) {
            // Dragons attack if player is in vicinity of its dragon hoard or itself
            if (enemies[i]->getCharacterID() == 'D') {

                pair<int, int> dragonHoardLoc = dynamic_cast<Dragon *>(enemies[i])->getDragonHoard()->getItemLoc();
                int distance = sqrt((player->getCharacterLoc().first - dragonHoardLoc.first) *
                                    (player->getCharacterLoc().first - dragonHoardLoc.first) +
                                    (player->getCharacterLoc().second - dragonHoardLoc.second) *
                                    (player->getCharacterLoc().second - dragonHoardLoc.second));

                if (distance <= sqrt(2)) {
                    player->attackedBy(*enemies[i]);
                    continue;
                }
            }
            int distance = sqrt((player->getCharacterLoc().first - enemies[i]->getCharacterLoc().first) *
                                (player->getCharacterLoc().first - enemies[i]->getCharacterLoc().first) +
                                (player->getCharacterLoc().second - enemies[i]->getCharacterLoc().second) *
                                (player->getCharacterLoc().second - enemies[i]->getCharacterLoc().second));
            if (distance <= sqrt(2) && enemies[i]->getIsHostile()) {
                // Enemy is in player vicinity
                player->attackedBy(*enemies[i]);
            } else {
                // Dragons don't move
                if (enemies[i]->getCharacterID() == 'D') continue;
                int xOffset = (rand() % 3) - 1;
                int yOffset = (rand() % 3) - 1;
                pair <int, int> newEnemyLoc =
                    make_pair (enemies[i]->getCharacterLoc().first + yOffset,
                               enemies[i]->getCharacterLoc().second + xOffset);

                while (!canEnemyMoveTo(newEnemyLoc)) {
                    xOffset = (rand() % 3) - 1;
                    yOffset = (rand() % 3) - 1;
                    newEnemyLoc = make_pair (enemies[i]->getCharacterLoc().first + yOffset,
                                             enemies[i]->getCharacterLoc().second + xOffset);
                }
                moveCharacter(*enemies[i], xOffset, yOffset);
            }
        }
        if (!gameOver)
            updateBoard();
    }
}


void Controller::moveCharacter(Character &character, int xOffset, int yOffset ) {
    pair<int, int> oldLoc = character.getCharacterLoc();
    pair<int, int> newLoc = make_pair (oldLoc.first + yOffset, oldLoc.second + xOffset);
    if (board.at(newLoc.first).at(newLoc.second) == '\\') {
        nextStage();
        isValidCommand = true;
        endTurn = true;
        return;
    }
    if (canPlayerMoveTo(newLoc)) {
        if (dynamic_cast<Player *>(&character)) {
            board.at(oldLoc.first).at(oldLoc.second) = oldFloorTile;
            oldFloorTile = board.at(newLoc.first).at(newLoc.second);
            isValidCommand = true;
        } else {
            board.at(oldLoc.first).at(oldLoc.second) = '.';
        }
        board.at(newLoc.first).at(newLoc.second) = character.getCharacterID();
        character.setCharacterLoc(newLoc.first, newLoc.second);
    } else if (board.at(newLoc.first).at(newLoc.second) == 'G' && dynamic_cast<Player *>(&character)){
        for (unsigned int i = 0; i < items.size(); i++) {
            if (items[i]->getItemLoc() == newLoc) {
                if (dynamic_cast<Treasure *>(items[i])->getObtainable()) {
                    items[i]->pickUp(*player);
                    board.at(oldLoc.first).at(oldLoc.second) = '.';
                    board.at(newLoc.first).at(newLoc.second) = character.getCharacterID();
                    character.setCharacterLoc(newLoc.first, newLoc.second);
                    isValidCommand = true;
                    break;
                } else {
                    // Dragon hoards are initially unobtainable, player should
                    // be able to walk over them
                    board.at(oldLoc.first).at(oldLoc.second) = oldFloorTile;
                    oldFloorTile = 'G';
                    board.at(newLoc.first).at(newLoc.second) = character.getCharacterID();
                    character.setCharacterLoc(newLoc.first, newLoc.second);
                    isValidCommand = true;
                    return;
                }
            }
        }
    }
}

void Controller::generateItems (Item** itemList, const int listLen) {
    for (int i = 0; i < 10; i++) {
        int itemType = rand() % listLen;
        int itemChamberID = rand () % chambers.size();
        pair<int, int> locItem = chambers.at(itemChamberID)->getRandomLoc();
        while (!canPlayerMoveTo(locItem)) {
            locItem = chambers.at(itemChamberID)->getRandomLoc();
        }
        // Create unique instance of treasure of specific amount(type) at the randomly
        // chosen index because we do not want to modify the original because it may
        // be chosen again
        Item * newItem = itemList[itemType]->copy();
        newItem->setItemLoc (locItem.first, locItem.second);

        items.push_back (newItem);
        place (locItem, (newItem->getItemID()));
        if (dynamic_cast<Treasure *>(newItem)) {
            dynamic_cast<Treasure *>(newItem)->placeDependencies();
        }
    }
}

void Controller::updateBoard () {
    view->update(board);
}

bool Controller::canPlayerMoveTo (std::pair<int, int> loc) {
    if (board.at(loc.first).at(loc.second) == '.' || board.at(loc.first).at(loc.second) == '#' ||
        board.at(loc.first).at(loc.second) == '+')
        return true;
    return false;
}

bool Controller::canEnemyMoveTo (std::pair<int, int> loc) {
    if (board.at(loc.first).at(loc.second) == '.')
        return true;
    return false;
}

void Controller::place (std::pair<int, int> loc, const char piece) {
    board.at(loc.first).at(loc.second) = piece;
}

bool Controller::placeCharacter (std::pair<int, int> loc, Enemy & enemy) {
    if (board.at(loc.first).at(loc.second) == '.') {
        place (loc, enemy.getCharacterID());
        enemies.push_back(&enemy);
        return true;
    }
    return false;
}

bool Controller::placeTreasure (std::pair <int, int> loc, Treasure * treasure) {
    if (board.at(loc.first).at(loc.second) == '.' ||
        board.at(loc.first).at(loc.second) == 'M' ||
        board.at(loc.first).at(loc.second) == 'H') {
        place (loc, treasure->getItemID());
        treasure->setItemLoc(loc.first, loc.second);
        items.push_back(dynamic_cast<Item *>(treasure));
        return true;
    }
    return false;
}

void Controller::generateRandomItemLocations() {
    ifstream mapFile(nameOfFile.c_str());
    string mapLine;
    while (true) {
        vector<char> line;
        vector<char> tempLine;
        getline (mapFile, mapLine);
        if (mapFile.eof())
            break;
        for (unsigned int i = 0; i < mapLine.length(); i++) {
            line.push_back (mapLine[i]);
            tempLine.push_back (mapLine[i]);
        }
        board.push_back (line);
        tempBoard.push_back (tempLine);
    }
    //Process Chamber Locations
    int currentChamberID = 0;
    for (unsigned int i = 0; i < tempBoard.size(); i++) {
        for (unsigned int j = 0; j< tempBoard.at(i).size(); j ++) {
            if (tempBoard.at(i).at(j) == '.') {
                Chamber * tempChamber = new Chamber (i, j, tempBoard, currentChamberID);
                chambers.push_back (tempChamber);
                currentChamberID++;
            }
        }
    }

    //Place Game Pieces
    //Place Player and Stair
    int playerChamberID, stairChamberID;
    playerChamberID = rand() % chambers.size();
    stairChamberID = rand() % chambers.size();
    while (stairChamberID == playerChamberID) {
        stairChamberID = rand() % chambers.size();
    }

    locPlayer = chambers.at(playerChamberID)->getRandomLoc();
    while (!canPlayerMoveTo(locPlayer)) {
        locPlayer = chambers.at(playerChamberID)->getRandomLoc();
    }

    place (locPlayer, player->getCharacterID());
    player->setCharacterLoc(locPlayer.first, locPlayer.second);

    locStair = chambers.at(stairChamberID)->getRandomLoc();
    while (!canPlayerMoveTo(locStair)) {
        locStair = chambers.at(stairChamberID)->getRandomLoc();
    }
    place (locStair, '\\');

    //Place Potions
    Item * potionList [6] = {new PoisonHealth (*this, 'P'), new RestoreHealth (*this, 'P'),
                           new WoundAtk (*this, 'P'), new BoostAtk(*this, 'P'),
                           new WoundDef (*this, 'P'), new BoostDef(*this, 'P')};
    generateItems (potionList, 6);
    // Generic treasure list to create treasures based on respective
    // probabilities
    Item * treasureList [8] = { new Treasure (*this, 2, 'G'),
                                new Treasure (*this, 2, 'G'),
                                new Treasure (*this, 2, 'G'),
                                new Treasure (*this, 2, 'G'),
                                new Treasure (*this, 2, 'G'),
                                new Treasure (*this, 6, 'G'),
                                new Treasure (*this, 1, 'G'),
                                new Treasure (*this, 1, 'G')};
    generateItems (treasureList, 8);

    //Place Enemies
    for (int i = 0; i < 20; i++) {
        int enemyType = rand() % 18;
        int enemyChamberID = rand() % chambers.size();
        std::pair<int, int> locEnemy = chambers.at(enemyChamberID)->getRandomLoc();
        while (!canPlayerMoveTo(locEnemy)) {
            locEnemy = chambers.at(enemyChamberID)->getRandomLoc();
        }
        Enemy * newCharacter;

        switch (enemyType) {
            case 0:
            case 1:
            case 2:
            case 3:
                //Generate Human
                newCharacter = new Human (*this, locEnemy, 'H');
                place (locEnemy, 'H');
                break;
            case 4:
            case 5:
            case 6:
                //Generate Dwarf
                newCharacter = new Dwarf (*this, locEnemy, 'W');
                place (locEnemy, 'W');
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                //Generate Halfling
                newCharacter = new Halfling (*this, locEnemy, 'L');
                place (locEnemy, 'L');
                break;
            case 12:
            case 13:
                //Generate Elf
                newCharacter = new Elf (*this, locEnemy, 'E');
                place (locEnemy, 'E');
                break;
            case 14:
            case 15:
                //Generate Orc
                newCharacter = new Orcs (*this, locEnemy, 'O');
                place (locEnemy, 'O');
                break;
            case 16:
            case 17:
                //Generate Merchant
                newCharacter = new Merchant (*this, locEnemy, 'M');
                place (locEnemy, 'M');
                break;
            default:
                break;
        }
        enemies.push_back (newCharacter);
    }

    // Free up memory in the 'temporary' array of potions and treasures
    for (int i = 0; i < 6; i++) {
        delete potionList[i];
    }
    for (int i = 0; i < 8; i++) {
        delete treasureList[i];
    }
}

void Controller::setHP(int health) {
    view->setHP(health);
}

void Controller::setAtk(int attack) {
    view->setAtk(attack);
}

void Controller::setDef(int defence) {
    view->setDef(defence);
}

void Controller::setGold(int amount) {
    view->setGold(amount);
}

int Controller::getGold() {
    return view->getGold();
}

void Controller::setAction (string action) {
    view->setAction(action);
}

string Controller::getAction() {
    return view->getAction();
}

void Controller::itemPickedUp(Item &item) {
    board.at(item.getItemLoc().first).at(item.getItemLoc().second) = '.';
    for (unsigned int i = 0; i < items.size(); i++) {
        if (items[i]->getItemLoc() == item.getItemLoc()) {
            delete items[i];
            items.erase(items.begin() + i);
            break;
        }
    }
}

void Controller::enemyDead(Enemy &enemy) {
    // Check if player is standing on gold. This only happens if a player has slain a Dragon
    // While standing on the dragon hoard
    if (oldFloorTile == 'G') {
        Dragon dragon = dynamic_cast<Dragon&>(enemy);
        Treasure *dragonHoard = dragon.getDragonHoard();
        player->pickUp(*dragonHoard);
        oldFloorTile = '.';
    }

    if (board.at(enemy.getCharacterLoc().first).at(enemy.getCharacterLoc().second) != 'G') {
        board.at(enemy.getCharacterLoc().first).at(enemy.getCharacterLoc().second) = '.';
    }
    for (unsigned int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getCharacterLoc() == enemy.getCharacterLoc()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            break;
        }
    }

    // Goblins steal 5 gold from every slain enemy
    if (race == "g") {
        setAction("PC steals 5 gold. " + getAction());
        setGold(getGold() + 5);
    }
}

void Controller::turnMerchantsHostile() {
    // If a merchant was attacked, all merchants should become hostile
    for (unsigned int i = 0; i < enemies.size(); i++) {
        enemies[i]->setIsHostile(true);
    }
    setHostile = true;
}

void Controller::playerWon() {
    cout << endl << "-------------------------------------------------------------------------------" << endl;
    cout << setw(46) << "Congratulations" << endl;
    cout << setw(48) << "You have beated cc3k" << endl;
    // Shades score is 1.5 times their gold
    int score = (race == "s") ? ceil(1.5 * getGold()) : getGold();
    cout << setw(47) << "Your final score: " <<  score << "" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "Would you like to play again? Y/N" << endl;
    string playAgain;
    cin >> playAgain;
    if (playAgain == "Y") {
        restart();
    } else {
        cout << "quitting..." << endl;
        return;
    }
}

void Controller::playerDied() {
    updateBoard();
    cout << endl << "-------------------------------------------------------------------------------" << endl;
    cout << setw(45) << "You have fainted" << endl;
    // Shades score is 1.5 times their gold
    int score = (race == "s") ? ceil(1.5 * getGold()) : getGold();
    cout << setw(46) << "Your final score: " <<  score << "" << endl;
    gameOver = true;
}

void Controller::restart() {
    cout << endl << "-------------------------------------------------------------------------------" << endl;
    cout << "Restaring..." << endl << endl;;

    // Delete enemies
    for (unsigned int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    enemies.clear();
    // Delete items
    for (unsigned int i = 0; i<items.size(); i++) {
        delete items[i];
    }
    items.clear();
    // Delete chambers
    for (unsigned int i = 0; i<items.size(); i++) {
        delete chambers[i];
    }
    chambers.clear();

    for (unsigned int i = 0; i < board.size(); i++) {
        board.at(i).clear();
    }
    board.clear();

    for (unsigned int i = 0; i < tempBoard.size(); i++) {
        tempBoard.at(i).clear();
    }
    tempBoard.clear();

    stageNumber = 1;
    view->setStage(stageNumber);

    oldFloorTile = '.';
    gameOver = false;
    delete player;

    if (isRandomlyGeneratedMap) initializeControllerRandom();
    else initializeControllerNotRandom();
}

void Controller::nextStage() {
    if (stageNumber == 5) {
        playerWon();
        gameOver = true;
        return;
    }
    stageNumber += 1;
    view->setStage(stageNumber);

    // Delete enemies
    for (unsigned int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    enemies.clear();
    // Delete items
    for (unsigned int i = 0; i<items.size(); i++) {
        delete items[i];
    }
    items.clear();

    for (unsigned int i = 0; i < board.size(); i++) {
        board.at(i).clear();
    }
    board.clear();

    for (unsigned int i = 0; i < tempBoard.size(); i++) {
        tempBoard.at(i).clear();
    }
    tempBoard.clear();

    // Reset player's atk and def to the original one of their race
    player->setAtk(player->getBaseAtk());
    player->setDef(player->getBaseDef());

    if (isRandomlyGeneratedMap) {
        // Delete chambers
        for (unsigned int i = 0; i < chambers.size(); i++) {
            delete chambers[i];
        }
        chambers.clear();
        initializeControllerRandom();
    } else {
        initializeControllerNotRandom();
    }
}
