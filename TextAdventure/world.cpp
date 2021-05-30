#include "world.h"
#include <iostream>

using namespace std;

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

bool World::hasInventoryItem(string itemName)
{
    auto i = find(inventory.begin(),inventory.end(),itemName); //iterator returns reference to a specific piece of memory
    if(*i != inventory.back()) // if the iterator isnt equal to items.back, it exists in the vector
    {
        return true;
        cout<<"returning true"<<endl;// if its the case... erase
    }
    else{
        cout<<"returning false"<<endl;
        return false;
    }
}

void World::removeFromInventory(string itemName)
{
    auto i = find(inventory.begin(),inventory.end(),itemName); //iterator returns reference to a specific piece of memory
    if(*i != inventory.back()) // if the iterator isnt equal to items.back, it exists in the vector
    {
        inventory.erase(i); // if its the case... erase
    }
    rooms[currentRoom].items.push_back(itemName);
}

void World::addToInventory(string itemName)
{
    inventory.push_back(itemName);
}

void World::get(string itemName)
{
    inventory.push_back(itemName); //item in invetory
    rooms[currentRoom].removeItem(itemName); //item out of room (method on room)
    //rooms[currentRoom]
}

void World::drop(string itemName)
{
    removeFromInventory(itemName);
    rooms[currentRoom].addItem(itemName);
}

void World::go(string roomName)
{
    for(int i = 0; i <rooms.size(); i++)
    {
        if(rooms[i].roomName == roomName)
        {
            auto a = find(rooms[currentRoom].adjacentRooms.begin(),rooms[currentRoom].adjacentRooms.end(),roomName);
            if(a != rooms[currentRoom].adjacentRooms.end())
            {
                currentRoom = i;
                cout<<rooms[currentRoom].description<<endl;
                return;
            }
            else{
                cout<<"That room isn't adjacent to the one you are currently in!"<<endl;
                return;
            }
        }
    }
    cout<<"No such room exists!"<<endl;
}

