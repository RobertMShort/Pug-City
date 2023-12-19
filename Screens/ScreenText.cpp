#include "ScreenText.hpp"

ScreenText::ScreenText()
{
    this->initFont();
}

void ScreenText::initFont()
{
    if (!this->font.loadFromFile("assets/VinaSans-Regular.ttf")) {
        std::cout << "ERROR: Failed to load font." << std::endl;
    }
}

void ScreenText::initText(sf::Text &text, unsigned int size, sf::Color color, float x, float y)
{
    text.setFont(this->font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    text.setString("None");
}

void ScreenText::updateText(std::string output, sf::Text &text)
{
    std::stringstream ss;
    ss << output;
        
    text.setString(ss.str());
}

void ScreenText::render(sf::RenderTarget &target, sf::Text &text)
{
    target.draw(text);
}
