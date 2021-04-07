#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>
#include <fstream>

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

using namespace std;
using namespace mssm;

void graphicsMain(Graphics& g)
{
    Image spriteRight ("spriteright.png");
    Image spriteLeft ("spriteleft.png");
    Image skull ("skull.png");
    int frameNum = 0;
    int spriteNum = 0;
    double spritePosX =  g.width()/2;
    int spriteSpeed = 15;
    bool goingRight = true;
    g.setBackground(WHITE);

    while (g.draw()) {
        //        double aspectRatio = 1.0*sprites.width()/sprites.height();
        //        g.image({100,100},  g.width()*aspectRatio, g.height(), sprites);
        if(g.isKeyPressed(Key::Left) && spritePosX > 0) {
            goingRight = false;

            cout<<"LEFT "<<spritePosX<<" frame: "<<frameNum<<endl;
            g.clear();
            spritePosX = spritePosX-spriteSpeed;
            frameNum =0;
            spriteNum++;


            if(spriteNum == 9)
            {
                spriteNum=0;
            }

        }

        if(g.isKeyPressed(Key::Right) && spritePosX< g.width()-116) {
            goingRight = true;
            frameNum = 0;
            cout<<"RIGHT "<<spritePosX<<endl;
            g.clear();
            spritePosX += spriteSpeed;
            frameNum =0;
            spriteNum++;
            if(spriteNum == 9)
            {
                spriteNum=0;
            }
        }
        if(goingRight){
            if (spriteNum <= 4){
                g.image({spritePosX,100}, 200, 200, spriteRight,spriteNum*116, 123, 116,95);

            }
            else{
                g.image({spritePosX,100}, 200, 200, spriteRight,(spriteNum-4)*116, 0, 116,95);
            }
        }
        else{
            if (spriteNum <= 4){
                g.image({spritePosX,100}, 200, 200, spriteLeft,spriteNum*116, 123, 116,95);

            }
            else{
                g.image({spritePosX,100}, 200, 200, spriteLeft,(spriteNum-4)*116, 0, 116,95);
            }
        }

        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }
    }
}

int main(int /*argc*/, char** /*argv*/)
{
    // main should be empty except for the following line:
    Graphics g("Graphics", 600, 600, graphicsMain);
    return 0;
}



