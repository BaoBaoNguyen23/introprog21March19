#ifndef WORLD_H
#define WORLD_H
#include "room.h"


class World
{
public:
    vector<Room> rooms;
    vector<string> inventory;
    int currentRoom;

public:
    bool hasInventoryItem(string itemName);     // return true if item is in inventory
     void removeFromInventory(string itemName);  // remove given item from the inventory
     void addToInventory(string itemName);     // add given item to the inventory
     void get(string itemName);  // pick something up
     void drop (string itemName);
     void go (string roomName);
};

#endif // WORLD_H
