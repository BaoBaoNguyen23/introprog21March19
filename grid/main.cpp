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

Vec2d rowColtoXY(Graphics& g, int boxWidth, int boxHeight, int row, int column){

    int columnWidth = boxWidth + 0;
    int rowHeight = boxHeight+10;
    int topMargin = 10;
    int leftMargin = 10;

    int x = column*columnWidth + leftMargin;
    int y = g.height() - (boxHeight+topMargin) - rowHeight*row;

    return {x,y};
}

Vec2d xyToRowCol(Graphics& g, int boxWidth, Vec2d pos, int boxHeight){

    int topMargin = 10;
    int leftMargin = 10;
    int columnWidth = boxWidth + 0;
    int rowHeight = boxHeight+10;

    int row = (pos.y + topMargin - g.height())/(-rowHeight);
    int col = (pos.x - leftMargin)/columnWidth;

    return {col, row};
}



void graphicsMain(Graphics& g)
{

    int numColumns =  10;
    int numRows = 10;
    int boxWidth = 30;
    int boxHeight = 30;

    vector<vector<bool>> grid(numRows, vector<bool>(numColumns, false));

    while (g.draw()) {
        g.clear();



        //        (g.width()-2*leftMargin)/columnWidth;


        for (int column = 0; column < numColumns; column++){
            for (int row = 0; row <numRows; row++){
                Color fillColor = BLACK;
                if(grid[row][column] == true){
                    fillColor = BLUE;
                }
                g.rect (rowColtoXY(g, boxWidth, boxHeight, row, column), boxWidth, boxHeight, GREEN, fillColor);
            }
        }
        //        Vec2d rc = xyToRowCol(g, boxWidth, boxHeight, g.mousePos());
        //        int currentRow = rc.y;
        //        int currentCol = rc.x;


        //        g.text({10,10}, 20, to_string(currentRow) + " " + to_string(currentCol));
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:{

                Vec2d rc = xyToRowCol(g, boxWidth, g.mousePos(), boxHeight);
                if (rc.y >= 0 && rc.y < numRows && rc.x >= 0 && rc.x < numColumns){
                    grid[rc.y][rc.x] = !grid[rc.y][rc.x];
                }
            }
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
