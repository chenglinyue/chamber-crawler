#include "item.h"
#include "controller.h"

using namespace std;

Item::Item (Controller & c, char id, string type) {
    itemID = id;
    controller = &c;
    itemType = type;
}

Item::~Item() {}

char Item::getItemID () {
    return itemID;
}

void Item::setItemID (char id) {
    itemID = id;
}

void Item::setItemLoc(int x, int y) {
    loc = make_pair (x, y);
}

void Item::pickedUp(Item *item) {
    controller->itemPickedUp(*item);
}

pair<int, int>Item::getItemLoc() {
    return loc;
}

string Item::getItemType() {
    return itemType;
}
