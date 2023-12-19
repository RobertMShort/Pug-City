#include "Building.hpp"

Building::Building(sf::Texture& texture, float pos_x, float pos_y, float scale_x, float scale_y)
{
    this->sprite.setTexture(texture, true);
    this->sprite.setPosition(pos_x, pos_y);
    this->sprite.setScale(scale_x, scale_y);
    
    
    this->initFont();
    this->initText();
    
    this->clock.restart();
}

void Building::move()
{
    if (this->sprite.getPosition().y > 449) {
        if (this->clock.getElapsedTime().asSeconds() > 2)
            this->sprite.move(0.f, -01.f);
    }
}

void Building::initFont()
{
    if (!this->font.loadFromFile("assets/VinaSans-Regular.ttf")) {
        std::cout << "ERROR: Failed to load font." << std::endl;
    }
}

void Building::initText()
{
    this->hitText.setFont(font);
    this->hitText.setCharacterSize(25);
    this->hitText.setFillColor(sf::Color::Red);
    this->hitText.setPosition(this->sprite.getGlobalBounds().left + 50, this->sprite.getGlobalBounds().height + 40);
    this->hitText.setString("None");
}

void Building::updateText()
{
    std::stringstream ss;
    ss << std::to_string(this->hitCount) + "/200";
        
    this->hitText.setString(ss.str());
}

void Building::update()
{
    switch (this->hitCount) {
        case 150: this->sprite.setColor(sf::Color::Red); break;
        case 175: this->sprite.setColor(sf::Color::Black); break;
    }
    
    this->updateText();
}

void Building::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
    
    
    if (this->hitCount < 200 && this->hitCount > 0)
        target.draw(this->hitText);
}
