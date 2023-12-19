#ifndef Building_hpp
#define Building_hpp

#include "Pug.hpp"

#include <iostream>
#include <sstream>

class Building : public Pug
{
private:
    sf::Clock clock;
    
    sf::Text hitText;
    sf::Font font;

public:
    Building(sf::Texture& texture, float pos_x, float pos_y, float scale_x, float scale_y);
    void move();
    
    void initFont();
    void initText();
    void updateText();
    
    void update();
    void render(sf::RenderTarget &target);
};

#endif /* Building_hpp */
