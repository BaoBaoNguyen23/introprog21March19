#ifndef SHIP_H
#define SHIP_H

#include "vec2d.h"
#include "graphics.h"


class Ship {
public:
    Vec2d  position;
    Vec2d  velocity;
    double  acceleration = 0;
    double angle = 0;
    double angularVelocity = 0;
    double scale{1};
    std::vector<Vec2d> points;
public:
    Ship(std::vector<Vec2d> points, mssm::Graphics& g);
    void update(mssm::Graphics& g);
    void draw (mssm::Graphics& g);


};

#endif // SHIP_H
