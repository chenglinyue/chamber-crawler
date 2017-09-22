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

const int NUMSTAGES = 0;

class Controller {
    std::pair <int, int> locPlayer;
    std::pair <int, int> locStair;
    std::vector <Enemy *> enemies;
    std::vector <std::vector<char> > board;
    std::vector <std::vector<char> > tempBoard;
    std::vector <Chamber *> chambers;
    std::vector <Item *> items;
    Board *view;
    Player *player;
    char oldFloorTile;
    bool setHostile;
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
    bool canPlayerMoveTo (std::pair<int, int> loc);
    bool canEnemyMoveTo (std::pair<int, int> loc);
    void place (std::pair<int, int> loc, const char piece);
    void generateItems (Item** itemList, const int listLen);
    void generateRandomItemLocations ();
    void moveCharacter(Character &character, int xOffset, int yOffset);
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
        bool placeCharacter (std::pair<int, int> loc, Enemy &enemy);
        bool placeTreasure (std::pair<int, int> loc, Treasure* item);
        void itemPickedUp(Item &item);
        void enemyDead(Enemy &enemy);
        void turnMerchantsHostile();
        void setHP(int health);
        void setAtk(int attack);
        void setDef(int defence);
        void setGold(int amount);
        int getGold();
        std::string getAction();
        void playerDied();
};

#endif
