#include "Plane.hpp"

void Plane::initSprite()
{
    this->texture.loadFromFile("assets/plane.png");
    this->sprite.setTexture(this->texture, true);
    this->sprite.setPosition(1100.f, 50.f);
    this->sprite.setScale(0.1f, 0.1f);
}

Plane::Plane()
{
    this->initSprite();
}

void Plane::move()
{
    if (this->sprite.getPosition().x > 500)
        this->sprite.move(-2.f, 0);
}

void Plane::update()
{
    switch (this->hitCount) {
        case 50: this->sprite.setColor(sf::Color::Red); break;
        case 75: this->sprite.setColor(sf::Color::Black); break;
    }
}

void Plane::render(sf::RenderTarget &target)
{
    if (this->hitCount < 100)
        target.draw(this->sprite);
}
