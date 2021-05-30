#include "room.h"
#include <iostream>
#include <string>

using namespace std;

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

void Room::print()
{
    cout<<endl;
    cout<<"-----------"<<endl;
    cout << roomName << " " << description << endl;
    cout<<"Here are the items present in the room:"<<endl;
    for (int i = 0; i < items.size(); i++){
        cout <<"-" <<items[i] << endl;
    }
    cout<<"Here are the adjacent rooms:"<<endl;
    for (int i = 0; i < adjacentRooms.size(); i++){
        if(adjacentRooms[i]!= ""){
        cout<< "-" << adjacentRooms[i] << endl;
        }
    }
}

string Room::getAdjacentRoom(int direction)
{
    if(direction >= 0 && direction <=3)
    {
    return adjacentRooms[direction];
    }
    else{
        cout<<"Direction index too big!"<<endl;
        return "";
    }

}

void Room::removeItem(string itemName)
{
    auto i = find(items.begin(),items.end(),itemName); //iterator returns reference to a specific piece of memory
    if(i != items.end()) // if the iterator isnt equal to items.back, it exists in the vector
    {
        items.erase(i); // if its the case... erase
    }
    else{
        cout<<"That item isn't in this room"<<endl;
    }
}

void Room::addItem(string itemName)
{
    items.push_back(itemName);
}

bool Room::hasItem(string itemName)
{
    auto i = find(items.begin(),items.end(),itemName); //iterator returns reference to a specific piece of memory
    if(i != items.end()) // if the iterator isnt equal to items.back, it exists in the vector
    {
       return true; // if its the case... erase
    }
   return false;
}
