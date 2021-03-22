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
    while (g.draw()) {
        g.clear();

        int boxWidth = 30;
        int boxHeight = 30;
        int numRows = 10;
        int columnWidth = 30;
        int rowHeight = boxHeight+10;
        int topMargin = 10;
        int leftMargin = 10;

        int numColumns = (g.width()-2*leftMargin)/columnWidth;


        for (int column = 0; column < numColumns; column++){
            for (int row = 0; row <numRows; row++){
                int x = column*columnWidth + leftMargin;
                int y = g.height() - (boxHeight+topMargin) - rowHeight*row;
                g.rect ({x, y}, boxWidth, boxHeight, GREEN);
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
    Graphics g("Graphics", 500, 500, graphicsMain);
    return 0;
}
