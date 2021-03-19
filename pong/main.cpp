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
    Sound music("/Users/bbao2019/Desktop/Pong.wav");

    while (g.draw()) {
        g.clear();

        g.text({100,300}, 20, "Ready to play some Pong?!!! (press any key to play)");
        for (const Event& e : g.events()){
            switch (e.evtType){
            case EvtType:: MousePress:
                g.play(music);
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
    Sound music(".wav");


   int ballSize = 20;
   int screenHeight = 600;
   int screenWidth = 600;
   int paddleHeight = 15;
   int paddleWidth = 60;

   Vec2d ballPosition{78,132};
   Vec2d ballVelocity{6.9,9.3};
   Vec2d paddlePlacement{4,0};
   Vec2d moveleft {-6,0};
   Vec2d moveright {6,0};

    while (g.draw()) {
           g.clear();

           g.rect(paddlePlacement, 60, 15, BLUE, WHITE);
            if (g.isKeyPressed(Key::Left)) {
               paddlePlacement = paddlePlacement + moveleft;
           }

            if (g.isKeyPressed(Key::Right)) {
                paddlePlacement = paddlePlacement + moveright;
            }

            if(ballPosition.y <= 15 + ballSize && ballPosition.x > paddlePlacement.x && ballPosition.x < (paddlePlacement.x + paddleWidth)){
             ballVelocity.y = -ballVelocity.y;
             ballPosition.y = 26;
       }

           g.ellipseC(ballPosition, ballSize, ballSize, BLUE, YELLOW);
           ballPosition = ballPosition + ballVelocity;
//cout << ballPosition.x << ballPosition.y << endl;
           if(ballPosition.y >= screenHeight-ballSize){
               ballVelocity.y = -ballVelocity.y;
           }
           if(ballPosition.x >= screenHeight-ballSize || ballPosition.x <= ballSize){
               ballVelocity.x= -ballVelocity.x;
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



