#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "character.h"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>

class Board;
class Enemy;
class Item;
class Player;
class Treasure;
class Chamber;

const int LAST_STAGE = 5;
const int NUM_ENEMIES = 20;
const int NUM_ITEMS = 10;
const int ENEMY_PROBABILITY = 18;
const int TREASURE_PROBABILITY = 8;
const int NUM_UNIQUE_POTION_TYPES = 6;
const int NUM_UNIQUE_ENEMY_TYPES = 7;
const int BOARD_HEIGHT = 25;

class Controller {
    std::pair <int, int> locPlayer; // stores location of player
    std::pair <int, int> locStair; // stores location of stairs
    std::vector <Enemy *> enemies; // vector containing all enemies in the current level
    std::vector <Chamber *> chambers; // vector containing all chambers in the current level
    std::vector <Item *> items; // vector containing all items in the current level
    std::vector <Item *> inventory; // vector containing all items in the player's inventory
    Board *view;
    Player *player;
    char oldFloorTile; // The last floor tile the player occupied
    bool setHostile; // Boolean to keep track of whether or not to set merchants hostile
    std::string race;
    bool isRandomlyGeneratedMap;
    int stageNumber;
    std::string nameOfFile;
    bool gameOver;
    bool endTurn;
    bool isValidCommand;

    void chooseCharacterRace();
    void playGame();
    void updateBoard ();
    bool canPlayerMoveTo (const std::pair<int, int> loc);
    bool canEnemyMoveTo (const std::pair<int, int> loc);
    void place (std::pair<int, int> loc, const char piece);
    void generateItems (Item** itemList, const int listLen);
    void generateRandomLocations ();
    void moveCharacter(Character &character, const int xOffset, const int yOffset);
    void playerWon();
    void nextStage();
    void restart();

    public:
        Controller();
        Controller(std::string fileName);
        ~Controller();
        void initializeControllerRandom();
        void initializeControllerNotRandom();
        void setAction (std::string action);
        bool placeEnemy (std::pair<int, int> loc, Enemy &enemy);
        bool placeTreasure (std::pair<int, int> loc, Treasure* item);
        void itemPickedUp(Item &item);
        void enemyDead(Enemy &enemy);
        void turnMerchantsHostile();
        void setHP(const int health);
        void setAtk(const int attack);
        void setDef(const int defence);
        void setGold(const int amount);
        int getGold();
        std::string getAction();
        void playerDied();
};

#endif
