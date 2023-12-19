#include "Missle.hpp"

Missle::Missle(sf::Texture &texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed) : Fire(texture, pos_x, pos_y, dir_x, dir_y, speed)
{
    //this->texture.loadFromFile("assets/missle.png");
    this->sprite.setTexture(texture, true);
    this->sprite.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->speed = speed;
    
    this->sprite.setScale(0.1f, 0.1f);
}

const sf::Vector2f& Missle::getPos() const
{
    return this->sprite.getPosition();
}
