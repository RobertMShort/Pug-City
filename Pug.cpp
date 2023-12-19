#include "Pug.hpp"

// PARENT CLASS

// Initializers
void Pug::initSprite()
{
    this->texture.loadFromFile("assets/pug.png");
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(0.f, 600.f);
    this->sprite.setScale(0.5f, 0.5f);
}

// Constructor/Deconstructor
Pug::Pug()
{
    this->speed = 5.f;
    this->hitCount = 0;
    
    this->initSprite();
    
    this->hpMax = 100;
    this->hp = this->hpMax;
    
    this->score = 0;
}

// Accessors
const sf::Vector2f& Pug::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Pug::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

int Pug::getHitCount()
{
    return this->hitCount;
}

const int& Pug::getHP() const
{
    return this->hp;
}
const int& Pug::getHPMax() const
{
    return this->hpMax;
}

int Pug::getScore()
{
    return this->score;
}

// Modifiers
void Pug::setHP(const int hp)
{
    this->hp = hp;
}

void Pug::loseHP(const int value)
{
    this->hp -= value;
    
    if (this->hp < 0)
        this->hp = 0;
}

void Pug::incrementHP(const int inc)
{
    this->hp += inc;
    
    if (this->hp > 100)
        this->hp = 100;
}

void Pug::resetScore()
{
    this->score = 0;
}

void Pug::incrementScore(const int inc)
{
    this->score += inc;
}

// Functions
void Pug::movePug(const float dirX)
{
    this->sprite.move(this->speed * dirX, 0);
}

void Pug::increment()
{
    this->hitCount += 1;
}

void Pug::update()
{
    if (this->hp <= 25 && this->hp > 15) {
        this->sprite.setColor(sf::Color::Red);
    } else if (this->hp <= 15 && this->hp > 0) {
        this->sprite.setColor(sf::Color::Black);
    } else {
        this->sprite.setColor(sf::Color::White);
    }

}

void Pug::render(sf::RenderTarget &target)
{
    if (this->hp > 0)
        target.draw(this->sprite);
}
