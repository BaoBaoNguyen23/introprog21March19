#ifndef BULLET_H
#define BULLET_H
#include "graphics.h"

class Bullet
{
public:
    Vec2d position;
    Vec2d velocity;
    int timer = 50;
public:
    Bullet(Vec2d position,double angle);
    void update(mssm::Graphics& g);
    void draw (mssm::Graphics& g);
};

#endif // BULLET_H
