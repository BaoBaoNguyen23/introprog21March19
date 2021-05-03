#ifndef WORLD_H
#define WORLD_H
#include "ship.h"
#include "graphics.h"
#include "bullet.h"
#include "asteroid.h"

class World
{
public:
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
    Ship ship;
public:

    World(Ship ship, mssm::Graphics& g);
    bool bulletCollision (Bullet bullet);
    void generateAsteroids (mssm::Graphics& g);
};



#endif // WORLD_H
