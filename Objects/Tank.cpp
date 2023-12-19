#include "Tank.hpp"

void Tank::initSprite()
{
    this->texture.loadFromFile("assets/tank.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(1100.f, 730.f);
    this->sprite.setScale(0.1f, 0.1f);
}

Tank::Tank()
{
    this->initSprite();
}

void Tank::render(sf::RenderTarget &target)
{
    if (this->hitCount < 100)
        target.draw(this->sprite);
}
