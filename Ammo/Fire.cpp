#include "Fire.hpp"

// PARENT CLASS 

Fire::Fire(sf::Texture &texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed)
{
    this->sprite.setTexture(texture);
    this->sprite.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->speed = speed;
    
    this->sprite.setScale(0.1f, 0.1f);
}

// Accessors
const sf::FloatRect Fire::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

// Functions
void Fire::update()
{
    this->sprite.move(this->speed * this->direction);
}

void Fire::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
