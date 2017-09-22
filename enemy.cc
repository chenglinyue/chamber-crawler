#include "enemy.h"
#include "shade.h"
#include "drow.h"
#include "goblin.h"
#include "troll.h"
#include "vampire.h"
#include <stdlib.h>
using namespace std;

// 3 param ctor
Enemy::Enemy(Controller &controller, std::pair<int, int>location, char id):Character(controller, location, id) {
    isHostile = true;
}

// Enemy attacks Player of race Goblin
void Enemy::attack(Goblin &goblin) {
    int miss = rand() % 2;
    if (isHostile) {
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + goblin.getDef()))*atk);
            goblin.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

// Enemy attacks Player of race Shade
void Enemy::attack(Shade &shade) {
    int miss = rand() % 2;
    if (isHostile) {
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + shade.getDef()))*atk);
            shade.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

// Enemy attacks Player of race Drow
void Enemy::attack(Drow &drow) {
    int miss = rand() % 2;
    if (isHostile) {
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + drow.getDef()))*atk);
            drow.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

// Enemy attacks Player of race Troll
void Enemy::attack(Troll &troll) {
    int miss = rand() % 2;
    if (isHostile) {
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + troll.getDef()))*atk);
            troll.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

// Enemy attacks Player of race Vampire
void Enemy::attack(Vampire &vampire) {
    int miss = rand() % 2;
    if (isHostile) {
        if (miss == 0) {
            int dmg = ceil((100.0/(100 + vampire.getDef()))*atk);
            vampire.takeDamage(dmg);
            doDamage(dmg);
        } else {
            missed();
        }
    }
}

// Notify controller to update action string
void Enemy::doDamage(const int dmg) {
    stringstream action;
    string enemyID;
    enemyID.push_back(charID);
    action << controller->getAction() << enemyID << " deals " << dmg
           << " damage to PC. ";
    controller->setAction(action.str());
}

// Enemies have 50% chance to miss against player
// Notify controller to update action string
void Enemy::missed() {
    stringstream action;
    string enemyID;
    enemyID.push_back(charID);
    action << controller->getAction() << enemyID << " attacked PC. " << enemyID<< " missed! ";
    controller->setAction(action.str());
}

// Notify controller that enemy died
void Enemy::dead() {
    stringstream action;
    action << controller->getAction() << "PC has slain " << charID << ". ";

    // Dead enemies randomly drop a small (value 1) or normal (value 2)
    // pile of gold that is directly picked up by player
    int amount = rand() % 2 + 1;
    action << "PC obtained " << amount << " gold. ";
    controller->setGold(controller->getGold() + amount);
    controller->setAction(action.str());
    controller->enemyDead(*this);
}

// setter for hostile field
void Enemy::setIsHostile(bool hostile) {
    isHostile = hostile;
}

// getter for hostile field
bool Enemy::getIsHostile() {
    return isHostile;
}
