#ifndef ScreenText_hpp
#define ScreenText_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class ScreenText
{
private:
    sf::Font font;
    sf::Text text;
public:
    ScreenText();
    void initFont();
    void initText(sf::Text &text, unsigned int size, sf::Color color, float x, float y);
    void updateText(std::string output, sf::Text &text);
    void render(sf::RenderTarget &target, sf::Text &text);
};

#endif /* ScreenText_hpp */
