#include "TankBullet.hpp"

TankBullet::TankBullet(sf::Texture &texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed) : Missle(texture, pos_x, pos_y, dir_x, dir_y, speed)
{
    //this->texture.loadFromFile("assets/tankBullet.png");
    this->sprite.setTexture(texture);
    this->sprite.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->speed = speed;
    
    this->sprite.setScale(0.04f, 0.04f);
}
