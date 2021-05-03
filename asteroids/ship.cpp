#include "ship.h"

using namespace std;
using namespace mssm;


Ship::Ship(std::vector<Vec2d> points,mssm::Graphics& g) // this is the constructor
{
    this->points = points;
    velocity = {1,0};
    position = {static_cast<double>(g.width()/2), static_cast<double>(g.height()/2)}; // i clicked the lightbulb and it told me how to do it... swag


}

void Ship::update(Graphics& g)
{
    position += velocity;
//    for (int i = 0; i < points.size(); i++){
//        points [i] += velocity;
//    }
    angle = angle + angularVelocity;
    Vec2d accelVec(acceleration,0);
    accelVec.rotate(angle);
    velocity = velocity + accelVec;



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

void Ship::draw(mssm::Graphics &g)
{
    vector<Vec2d> copyPoints = points;
    copyPoints.push_back(points[0]);


    for (int i = 0; i < copyPoints.size(); i++){
        copyPoints[i].rotate(angle+M_PI/2);
        Vec2d offset{-12,0};
        offset.rotate(angle);
        copyPoints [i] += position - offset;
        copyPoints[i] = copyPoints[i] *scale;

    }
    g.polyline(copyPoints,WHITE);
}
