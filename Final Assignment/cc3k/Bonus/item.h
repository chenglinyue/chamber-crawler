#ifndef ITEM_H
#define ITEM_H

#include <iostream>

class Player;
class Controller;

class Item {
    protected:
        char itemID;
        Controller * controller;
        std::pair<int, int> loc;
        std::string itemType;
    public:
        Item (Controller & c, char id, std::string type);
        virtual ~Item();
        char getItemID ();
        void setItemID (char id);
        void setItemLoc (int x, int y);
        std::pair<int, int> getItemLoc();
        virtual void pickUp(Player &player) = 0;
        virtual Item* copy () = 0;
        void pickedUp(Item *item);
        std::string getItemType();
};

#endif
