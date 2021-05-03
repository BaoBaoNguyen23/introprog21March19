#include "bullet.h"
using namespace mssm;
Bullet::Bullet(Vec2d position, double angle)
{
    this->position = position;
    velocity = {-10,0};
    velocity.rotate(angle);

}

void Bullet::update(mssm::Graphics &g)
{
    position = position + velocity;
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

void Bullet::draw(mssm::Graphics &g)
{
    g.point(position,WHITE);
}
