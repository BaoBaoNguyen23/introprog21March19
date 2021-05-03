#include <iostream>
#include <memory>
#include "graphics.h"
#include <cmath>
#include <fstream>
#include "ship.h"
#include "asteroid.h"
#include "bullet.h"

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wnarrowing"

using namespace std;
using namespace mssm;

//void drawShip(Graphics& g, Ship s)
//{
//    vector<Vec2d> points {
//        {-20,-20},
//        {0,-10},
//        {20,-20},
//        {0,30}
//    };

//    for (int i = 0; i < points.size(); i++) {
//        points[i].rotate(s.angle);
//        points[i] = points[i] * s.scale;
//        points[i] = points[i] + s.position;  // translation
//    }

//    g.polygon(points, WHITE);
//}

void simulatePhysics(Ship& ship)
{

}


bool checkCollisions (Ship ship, Asteroid ast){
    double xVal= (abs(ast.position.x - ship.position.x));
    double yVal = abs(ast.position.y - ship.position.y);


    if (abs(ast.position.x - ship.position.x) <= ((2*ast.scale*4)+10) &&
            abs(ast.position.y - ship.position.y) <= (2*ast.scale*4)+10){

        return true;
    }
    return false;
}

bool bulletCollisions (Bullet bullet, Asteroid ast){
    double xVal= (abs(ast.position.x - bullet.position.x));
    double yVal = abs(ast.position.y - bullet.position.y);


    if (abs(ast.position.x - bullet.position.x) <= ((2*ast.scale*4) + 20) &&
            abs(ast.position.y - bullet.position.y) <= (2*ast.scale*4) + 20){
        cout<<"hit"<<endl;
        return true;
    }
    return false;
}

void graphicsMain(Graphics& g)
{

    while(g.draw())
    {
        g.clear();
        g.text(g.width()/2-250,g.height()/2,30,"Welcome to space! Press 'p' to begin!");
        g.text(g.width()/2-260,g.height()/2-50,20,"Controls are WASD (space to shoot)... Play at your own risk!!", RED);

        if(g.isKeyPressed('P')){
            break;
        }
    }

    bool gameOver = false;
    int score = 0;
    Ship ship({{0, 30}, {-20, -10}, {0, 0}, {20, -10}},g);
    vector <Bullet> bullets;
    vector <Asteroid> asteroids;
    int round = 0;
    int lives = 3;


    while (g.draw()) {
        g.clear();

        if(asteroids.size() == 0){
            round++;
            ship.velocity = {1,0};
            ship.position = {g.height()/2,g.width()/2};
            for (int i = 0; i < 10+round; i++){
                int parity = g.randomInt(1,10);
                parity = parity%2;
                double xSpawn;
                double ySpawn;
                if (parity == 1){
                    xSpawn = g.randomInt(1,g.width()/2-125);
                    ySpawn = g.randomInt(1, g.height()/2-125);
                }
                else{
                    xSpawn = g.randomInt(g.width()/2+125, g.width());
                    ySpawn = g.randomInt(g.height()/2+125, g.height());
                }
                Asteroid ast ({xSpawn,ySpawn},min(g.randomDouble(1*round, 3*round),10.0),g);
                asteroids.push_back(ast);
            }
        }
        g.text({g.width()/4,g.height()-20},20,"Round " + to_string(round), WHITE);
        g.text({2*g.width()/4,g.height()-20},20,"Score " + to_string(score), WHITE);
        g.text({3*g.width()/4,g.height()-20},20,"Lives " + to_string(lives), WHITE);
        if(gameOver == true)
        {
            g.text(g.width()/2-200,g.height()/2,20,"How'd you die 3 times?? Press 'P' to play again");
            if(g.isKeyPressed('P'))
            {
                gameOver = false;
                asteroids.clear();
                score = 0;
                lives = 3;
                round = 0;

            }

        }
        else{

//        if(g.isKeyPressed(' '))
//        {
//            bullets.push_back({ship.position, ship.angle});
//        }

        if(g.isKeyPressed('A'))
        {
            ship.angularVelocity = 0.15;
        }
        else if(g.isKeyPressed('D'))
        {
            ship.angularVelocity = -0.15;
        }
        else if(g.isKeyPressed('W'))
        {
            ship.acceleration = -0.25;
        }
        else
        {
            ship.acceleration =0;
            ship.angularVelocity = 0;
        }
        for (int i = 0; i < asteroids.size(); i++){
            if(checkCollisions(ship, asteroids[i])){
                lives--;
                if(lives > 0)
                {
                   asteroids.clear();

                   round --;
                }
                else{
                    gameOver = true;
                }
                g.ellipseC(ship.position,60,60,{255,165,0},{255,165,0});
                 g.ellipseC({ship.position.x+10,ship.position.y+10},60,60,{255,165,0},{255,125,0});
                 g.ellipseC({ship.position.x+5,ship.position.y-5},40,40,{255,69,10},{255,69,10});

            }
        }
        if(bullets.size() > 0){
        for(int j = 0; j <bullets.size(); j++){
            for (int i = 0; i < asteroids.size(); i++){
                if(bulletCollisions(bullets[j], asteroids[i])){
                    if(asteroids[i].scale > 1)
                    {
                        Asteroid ast1{asteroids[i].position,asteroids[i].scale/2,g};
                        Asteroid ast2{asteroids[i].position,asteroids[i].scale/2,g};
                        ast1.velocity = asteroids[i].velocity;
                        ast2.velocity = {-1*ast1.velocity.x,ast1.velocity.y};
                        asteroids.push_back(ast1);
                        asteroids.push_back(ast2);
                        if(asteroids[i].scale >= 2.5)
                        {
                            score += 20;
                        }
                        else if(asteroids[i].scale >= 1.5)
                        {
                            score += 50;
                        }

                    }
                    if(asteroids[i].scale <= 1.5)
                    {
                        score += 100;
                    }
                    asteroids.erase(asteroids.begin()+i);
                    bullets.erase(bullets.begin()+j);
                    break;
                }
            }
            }
        }

        ship.draw(g);

        for (int i = 0; i < asteroids.size(); i++){
            asteroids[i].draw(g);
            asteroids[i].update(g);
        }

        for (int i = 0; i < bullets.size(); i++){

            if(bullets[i].timer == 0){
                bullets.erase(bullets.begin()+i);
            }
            else{
                bullets[i].timer --;
                bullets[i].draw(g);
                bullets[i].update(g);
            }
        }

        ship.update(g);
        cout << ship.position.x << " " << ship.position.y << endl;

        simulatePhysics(ship);

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
                if (e.arg == ' '){
                    bullets.push_back({ship.position, ship.angle}); // prevents cringe spam meta
                }
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }
    }
    }

}

int main(int /*argc*/, char** /*argv*/)
{
    // main should be empty except for the following line:
    Graphics g("Graphics", 600, 600, graphicsMain);
    //return 0;
}
