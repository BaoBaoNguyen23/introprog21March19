#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

using namespace std;
using namespace mssm;

void welcomePage (Graphics& g){


    while (g.draw()) {
        g.clear();

        g.text({100,300}, 20, "Ready to play some Pong?!!! (press any key to play)");
        for (const Event& e : g.events()){
            switch (e.evtType){
            case EvtType:: MousePress:
                return;
            case EvtType::KeyPress:
                return;
            default:
                break;
            }
        }

    }
     Sound music("/Users/bbao2019/Desktop/Pong.wav");
}

void endGame (Graphics& g, int score){

    while (g.draw()) {
        g.clear();

        g.text({100,300}, 20, "You Lost...");
        g.text({100,250},20, "Score: " + to_string(score));
        for (const Event& e : g.events()){
            switch (e.evtType){
            case EvtType:: MousePress:
                break;
            case EvtType::KeyPress:
                return;
            default:
                break;
            }
        }

    }
}

void graphicsMain(Graphics& g)
{
    welcomePage(g);
    Sound music("/Users/bbao2019/Desktop/Pong.wav");

    Color color = {255,255,255};
    int ballSize = 20;
    int paddleWidth = 60;
    int lives = 3;
    int score = 0;

    Vec2d ballPosition{78,132};
    Vec2d ballVelocity{6.9,9.3};
    double originalSpeed = ballVelocity.magnitude();
    Vec2d paddlePlacement{4,0};
    int paddleSpeed = 15;


    while (g.draw()) {
        g.clear();

        g.text({g.width()/2 +50, g.height()-25},20, "Speed Multiplier: " + to_string(ballVelocity.magnitude()/originalSpeed), color);
        g.text({g.width()/2 -250, g.height()-25},20, "Score: " + to_string(score), color);
        g.text({g.width()/2-50, g.height()-25},20, "Lives: " + to_string(lives), color);

        g.rect(paddlePlacement, 60, 15, color, color);
        if (g.isKeyPressed(Key::Left) && paddlePlacement.x > 0) {
            paddlePlacement.x -= paddleSpeed;
        }

        if (g.isKeyPressed(Key::Right) && paddlePlacement.x < g.width()-paddleWidth) {
            paddlePlacement.x += paddleSpeed;
        }

        if(ballPosition.y <= 15 + ballSize && ballPosition.x > paddlePlacement.x && ballPosition.x < (paddlePlacement.x + paddleWidth)){
            ballVelocity.y = -ballVelocity.y;
            ballPosition.y = 26;
            score ++;
            ballVelocity = ballVelocity * 1.025;
            g.play(music);
            color.r -= 10;
            color.g -= 20;
            color.b -= 30;
        }

        g.ellipseC(ballPosition, ballSize, ballSize, color, color);
        ballPosition = ballPosition + ballVelocity;
        //cout << ballPosition.x << ballPosition.y << endl;
        if(ballPosition.y >= g.height()-ballSize){
            ballVelocity.y = -ballVelocity.y;
        }
        if(ballPosition.x >= g.height()-ballSize || ballPosition.x <= ballSize){
            ballVelocity.x= -ballVelocity.x;
        }
        if (ballPosition.y <= 0){ //THIS IS WHERE DYING HAPPENS
            ballPosition = {g.width()/2, g.height()/2};
            ballVelocity = {6.9,9.3};
            if (lives == 1){
                lives = 3;
                color = {255,255,255};
                int oldscore = score;
                score = 0;
                endGame(g,oldscore);
            }
            else {
                lives = lives - 1;
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

//bool verticalCollision (int screenHeight, int ballPosition, int ballHeight){
//   return ballPosition
//}


//void graphicsMain(Graphics& g)
//{
//    TextMetrics textMetrics;

//    string message = "This is a text";

//    Vec2d pos{g.width()/2, g.height()/2};

//    while (g.draw()) {
//        g.clear();

//        // line using x1,y1,x2,y2
//        g.line(50,100,200,300,GREEN);

//        // line using two points
//        Vec2d p1{55,100};
//        Vec2d p2{205,300};
//        g.line(p1,p2,YELLOW);

//        // line with two points more compactly
//        g.line({60,100},{210,300},RED);

//        g.ellipse(20,200,50,50,WHITE);
//        g.ellipse(20,200,150,50,YELLOW);
//        g.ellipse(20,200,50,150,RED);

//        for (int i = 0; i < 100; i++) {
//            double x = g.randomDouble(50,150);
//            double y = g.randomDouble(400,500);
//            g.point(x,y,PURPLE);
//        }

//        g.text(10,g.height()-40,20,"We are using a right-handed coordinate system");
//        g.text(10,g.height()-70,20,"the point (0,0) is in the lower left");
//        g.text(0,0,50,"(0,0)");

//        g.text(pos, 20, message, YELLOW);

//        double w;
//        double h;
//        Vec2d rectPos;

//        textMetrics.rect(pos, message, 20, rectPos, w, h);

//        g.rect(rectPos, w, h, GREEN);


//        for (const Event& e : g.events())
//        {
//            switch (e.evtType)
//            {
//            case EvtType::MousePress:
//                pos = Vec2d{e.x, e.y};
//                message = "MousePress";
//                break;
//            case EvtType::MouseRelease:
//                pos = Vec2d{e.x, e.y};
//                message = "MouseRelease";
//                break;
//            case EvtType::MouseWheel:
//                break;
//            case EvtType::MouseMove:
//                pos = Vec2d{e.x, e.y};
//                message = "MouseMove";
//                break;
//            case EvtType::KeyPress:
//                message = "KeyPress: ";
//                if (isprint(e.arg)) {
//                    message.append(1, char(e.arg));
//                }
//                else {
//                    message.append(to_string(e.arg));
//                }
//                break;
//            case EvtType::KeyRelease:
//                message = "KeyRelease: ";
//                if (isprint(e.arg)) {
//                    message.append(1, char(e.arg));
//                }
//                else {
//                    message.append(to_string(e.arg));
//                }
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
    Graphics g("Graphics", 600, 600, graphicsMain);
    return 0;
}



