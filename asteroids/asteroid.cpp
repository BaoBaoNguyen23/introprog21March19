#include "asteroid.h"

using namespace std;
using namespace mssm;


Asteroid::Asteroid(Vec2d position, double scale, mssm::Graphics &g)
{
    this->scale = scale;
    this->position = position;

    for (int i = 0; i < points.size(); i++){
        points[i] = points[i] - Vec2d{-2.5,18};
        points[i] = points[i] * scale;
    }
    velocity = {static_cast<double>(g.randomInt(1,2)),static_cast<double>(g.randomInt(1,2))};


}

void Asteroid::update(mssm::Graphics &g)
{
    position += velocity;
    angle = angle + angularVelocity;


    if (position.y < 0) {
        position.y = g.height();
    }
    if (position.y > g.height()) {
        position.y = 0;
    }
    if (position.x < 0) {
        position.x = g.width();
    }
    if (position.x > g.width()) {
        position.x = 0;
    }
}

void Asteroid::draw(mssm::Graphics &g)
{
    vector<Vec2d> copyPoints = points;
    copyPoints.push_back(points[0]);

    for (int i = 0; i < copyPoints.size(); i++){
        copyPoints[i].rotate(angle+M_PI/2);

        copyPoints [i] += position;

    }
    g.polyline(copyPoints,WHITE);
}


