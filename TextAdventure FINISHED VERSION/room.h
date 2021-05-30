#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>

using namespace std;


class Room
{
public:
    string roomName;
    string description;
    vector<string> adjacentRooms;
    vector<string> items;



public:
    void print();
    string getAdjacentRoom(int direction);   // direction is number 1-4 indicating North/South/East/West
    void removeItem(string itemName);
    void addItem(string itemName);
    bool hasItem (string itemName);
};

#endif // ROOM_H
