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

bool isFull (vector<vector<int>> grid){
    for (vector<int> column:grid){
        for(int box : column){
            if (box == 0){
                return false;
            }
        }
    }
    return true;
}

int diagonalRight(vector<vector<int>>grid){
    for (int x =5; x>=3; x--){
        for(int y=0; y <=3; y++){
            int p1 = 0;
            int p2 = 0;

            for(int i=0; i<4; i++){
                if(grid[x-i][y+i]==1)
                {
                    p1++;
                }
                else if(grid[x-i][y+i]==2){
                    p2++;
                }
                else{
                    break;
                }
            }
            if (p1 ==4){
                return 1;
            }
            if (p2 ==4){
                return 2;
            }
        }
    }
    return 0;

}

int diagonalLeft(vector<vector<int>>grid){
    for (int x =5; x>=3; x--){
        for(int y=6; y >=3; y--){
            int p1 = 0;
            int p2 = 0;

            for(int i=0; i<4; i++){
                if(grid[x-i][y-i]==1)
                {
                    p1++;
                }
                else if(grid[x-i][y-i]==2){
                    p2++;
                }
                else{
                    break;
                }
            }
            if (p1 ==4){
                return 1;
            }
            if (p2 ==4){
                return 2;
            }
        }
    }
    return 0;
}
int whoWon(vector<vector<int>> grid){
    int p1 = 0;
    int p2 = 0;
    for (int y=0; y<6; y++){
        for (int x=0; x<4; x++){
            for (int i=0; i<4; i++){
                if(grid[y][x+i] == 1){
                    p1++;
                }
                else if (grid[y][x+i] == 2){
                    p2++;
                }
                else{
                    break;
                }
            }
            if (p1 ==4){
                return 1;
            }
            if (p2 ==4){
                return 2;
            }
            p1 =0;
            p2 = 0;
        }
        p1 =0;
        p2 = 0;
    }
    p1 = 0;
    p2 = 0;
    for (int x=0; x<grid.size(); x++){
        for (int y=0; y<3; y++){
            for (int i=0; i<4; i++){
                if(grid[y+i][x] == 1){
                    p1++;
                }
                else if (grid[y+i][x] == 2){
                    p2++;
                }
                else{
                    break;
                }
            }
            if (p1 ==4){
                return 1;
            }
            if (p2 ==4){
                return 2;
            }
            p1 =0;
            p2 = 0;
        }
        p1 =0;
        p2 =0;
    }

    if(diagonalLeft(grid))
    {
        return diagonalLeft(grid);
    }
    if(diagonalRight(grid))
    {
        return diagonalRight(grid);
    }
    if (isFull(grid)){
        return 3;
    }
    return 0;
}



Vec2d rowColtoXY(Graphics& g, int boxWidth, int boxHeight, int row, int column){

    int columnWidth = boxWidth ;//+ 10;
    int rowHeight = boxHeight ;//+10;
    int topMargin = g.height()/5;
    int leftMargin = g.width()/6.5;

    int x = column*columnWidth + leftMargin;
    int y = g.height() - (boxHeight+topMargin) - rowHeight*row;

    return {x,y};
}

Vec2d xyToRowCol(Graphics& g, int boxWidth, Vec2d pos, int boxHeight){

    int topMargin = g.height()/5;
    int leftMargin = g.width()/6.5;
    int columnWidth = boxWidth + 0;
    int rowHeight = boxHeight;//+10;

    int row = (pos.y + topMargin - g.height())/(-rowHeight);
    int col = (pos.x - leftMargin)/columnWidth;
    cout<<row<<" "<<col<<endl;
    return {col, row};
}

bool nextRowFull (vector<vector<int>> grid,int row, int col){
    if (grid[row+1][col] == 0){
        return false;
    }
    return true;
}
void dropToken(Graphics& g, vector<vector<int>>& grid, int col, bool& playerOneTurn){

    int numRows = 6;
    //check whether at the bottom or in the grid

    for (int row=numRows-1; row>=0; row--){
        if(grid[row][col] == 0){
            playerOneTurn = !playerOneTurn;
            grid[row][col]=playerOneTurn+1;

            break;
        }

    }
}



void graphicsMain(Graphics& g)
{
    int winner;

    int numColumns =  7;
    int numRows = 6;
    //int grid[numColumns][numRows];
    vector<vector<int>> grid(numRows, vector<int>(numColumns, 0));// - hamlin's version*/
    //    vector<vector<int>> grid(numColumns, vector<int>(numRows, 0));
    //    for(int i =0; i<7;i++)
    //    {
    //        vector<int> vec{0,0,0,0,0,0};
    //        grid.push_back(vec);
    //    }

    int boxWidth = 50;
    int boxHeight = 50;
    //    int column = 10;


    bool isGameOver = false;

    bool playerOneTurn = true; // when this is true, it is player 1's turn. when false it player 2 turn!!

    while (g.draw()) {
        g.clear();



        //        (g.width()-2*leftMargin)/columnWidth;

        if(playerOneTurn)
        {
            g.text(g.width()/2-75,g.height()-g.height()/8,20,"Player One's Turn",RED);
        }
        else
        {
            g.text(g.width()/2-75,g.height()-g.height()/8,20,"Player Two's Turn",YELLOW);
        }
        for (int column = 0; column < numColumns; column++){
            for (int row = 0; row <numRows; row++){
                Color fillColor = BLACK;
                if(grid[row][column] == 1){
                    fillColor = RED;
                }
                else if(grid[row][column] == 2){
                    fillColor = YELLOW;
                }
                else{
                    fillColor = BLACK;
                }

                g.ellipse (rowColtoXY(g, boxWidth, boxHeight, row, column), boxWidth, boxHeight, WHITE, fillColor);
            }
        }
        Vec2d rc = xyToRowCol(g, boxWidth, g.mousePos(), boxHeight);
        int currentRow = rc.y;
        int currentCol = rc.x;


        g.text({10,10}, 20, to_string(currentRow) + " " + to_string(currentCol));
        if (winner){
            isGameOver = true;
            if (winner==3){
                g.text (g.width()/2-160, g.height()/20,25,{"Draw! Press any key to reset"});
            }
            else if(winner==1){
                g.text (g.width()/2-160, g.height()/20,20,{"Player "+to_string(winner)+" wins! Press any key to reset"},RED);
            }
            else{
                g.text (g.width()/2-160, g.height()/20,20,{"Player "+to_string(winner)+" wins! Press any key to reset"},YELLOW);
            }

        }
        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:{
                if(!isGameOver){
                    Vec2d rc = xyToRowCol(g, boxWidth, g.mousePos(), boxHeight);
                    int col = rc.x;
                    dropToken(g,grid,col,playerOneTurn);
                    winner = whoWon(grid);
                }
                break;
            }
            case EvtType::MouseRelease:{
                break;
            }
            case EvtType::MouseWheel:{
                break;
            }
            case EvtType::MouseMove:{
                break;
            }
            case EvtType::KeyPress:{
                for (int i=0; i<grid.size(); i++){
                    for (int j=0; j<grid[i].size(); j++){
                        grid [i][j] = 0;
                    }
                }
                playerOneTurn = true;
                isGameOver = false;
                winner = 0;
                break;
            }
            case EvtType::KeyRelease:{
                break;
            }
            default:
                break;
            }
        }
    }
}

//void endGame (Graphics& g, vector<vector<int>>& grid){

//    while (g.draw()) {
//        g.clear();

//        //        TextMetrics textMetrics; only to center

//        g.text({100,300}, 20, "You Lost... (press any key to continue)");
//        for (const Event& e : g.events()){
//            switch (e.evtType){
//            case EvtType:: MousePress:
//                break;
//            case EvtType::KeyPress:

//                break;
//            default:
//                break;
//            }
//        }
//    }
//}

int main(int /*argc*/, char** /*argv*/)
{
    // main should be empty except for the following line:
    Graphics g("Graphics", 500, 500, graphicsMain);
    return 0;
}

