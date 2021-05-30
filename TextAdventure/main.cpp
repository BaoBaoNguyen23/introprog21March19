#include <iostream>
#include <vector>
#include <string>
#include "world.h"
#include "room.h"
using namespace std;

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"


int main() // North, East, South, West
{

    World world{{

            {"Bedroom", "You are in the Bedroom. There is nobody here and the windows are barred. In the corner, there's a little safe. It's locked. The bedsheets are made out of cotton. ",{"Kitchen", "Bathroom","",""}, {"Bed", "Safe", "BloodyCarpet", "Closet", "BasketballHoop"}},
            {"Bathroom", "You are in the Bathroom. It is a contemporary style bathroom with polished hardwood. There are granite countertops and a running sink. ", {"", "", "", "Bedroom", ""}, {"Sink", "Tub with body", "Toothbrush"}},
            {"Kitchen", "You are in the Kitchen. It is a modern styled bathroom with deluxe appliances, large working islands, and food prep zones.", {"Garden", "Pantry", "Bedroom", ""}, {"BloodyKnife", "FruitBowl", "Keurig", "SkilletWithEggs"}},
            {"Pantry", "You are in the Pantry. ", {"Garden", "","", "Kitchen"}, {"Cereal", "BrokenClock", "Broom"}},
            {"Garden","Description", {"PoolHouse", "Pool", "Pantry", "Kitchen"}, {"Flower", "Hose", "Glove", "Chair"}},
            {"PoolHouse", "Description", {"", "Pool", "Garden"}, {"Key", "Drugs", "Sofa", "CoffeeTable"}},
            {"Pool", "Description", {"PoolHouse", "", "Garden"}, {"DivingBoard", "BeachBall", "PoolFloaties"}}
                }
                ,{},0
               };

    while(true){
        world.rooms[world.currentRoom].print();
        string input;
        string firstWord;
        cout << "What do you want to do?" << endl;
        cin >> input;
        if (input == "go"){
            cout << "Where would you like to go?" << endl;
            string room;
            cin>>room;
            world.go(room);
        }
        if (input == "take"){
            cout << "What item would you like to take?" << endl;
            string itemName;
            cin>> itemName;
            if (world.rooms[world.currentRoom].hasItem(itemName)){
                world.get(itemName);
                cout << "Got " << itemName << endl;
            }
            else {
                cout << "The item you selected is not in this room" << endl;
            }
        }
        if(input == "help")
        {
            cout<<"Here are the commands you can do:"<<endl;
            cout<<"inventory : view your inventory"<<endl;
            cout<<"take : brings up prompt to take item from room"<<endl;
            cout<<"use : brings up prompt to use item"<<endl;
        }
        if(input == "use")
        {
            string itemName;
            cout<<"what item would you like to use?"<<endl;
            cin >> itemName;
            if(itemName == "Key")
            {
                if(world.rooms[world.currentRoom].roomName == "Bedroom")
                {
                    cout<<"You unlock the safe to find the intel you came for. You slip out of the house and return to headquarters. Nice work."<<endl;
                    return 0;
                }
                else{
                    cout<<"You don't see anything in this room to unlock."<<endl;
                }
            }
            cout<<"This has no effect."<<endl;
        }
        if (input == "inventory"){
            if(world.inventory.size())
            {
                cout<<"Here's your inventory:"<<endl;
                for(int i = 0; i< world.inventory.size(); i++)
                {
                    cout<<"-"<<world.inventory[i]<<endl;
                }
            }
            else {
                cout << "Your inventory is empty" << endl;
            }
        }
    }

    return 0;
}
