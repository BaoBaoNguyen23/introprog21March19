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

void drawSquare (Graphics& g, Vec2d center, double width){
    Vec2d pointOne  {center.x - (width/2), center.y + (width/2)};
    Vec2d pointTwo  {center.x - (width/2), center.y - (width/2)};
    Vec2d pointThree  {center.x + (width/2), center.y - (width/2)};
    Vec2d pointFour  {center.x + (width/2), center.y + (width/2)};

    g.polygon ({pointOne, pointTwo, pointThree, pointFour}, {50, 28, 32}, {225, 198, 153});

    if (width > 10){
        drawSquare(g, pointOne, width/2);
        drawSquare(g, pointTwo, width/2);
        drawSquare(g, pointThree, width/2);
        drawSquare(g, pointFour, width/2);

    }

}

void graphicsMain(Graphics& g)
{


    while (g.draw()) {
        g.clear();

        drawSquare(g, {g.width()/2, g.height()/2}, 400);

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
            case EvtType::KeyPress:
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



