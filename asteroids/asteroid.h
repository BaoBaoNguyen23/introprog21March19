#ifndef ASTEROID_H
#define ASTEROID_H

#include "graphics.h"


class Asteroid
{
public: // fields are variables to specific to a single class
    std::vector<Vec2d> points = {{-10, 23}, {-12, 11}, {-5, 8}, {6,9}, {7,15}, {5, 25}, {-4, 27}};
    Vec2d  position;
    Vec2d  velocity;
    double angle = 0;
    double angularVelocity = 0;
    double scale;

public: // methods are functions that are specific to a class
    Asteroid(Vec2d position, double scale, mssm::Graphics& g);
    void update(mssm::Graphics& g);
    void draw (mssm::Graphics& g);
};

#endif // ASTEROID_H
