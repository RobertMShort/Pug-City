#ifndef Win_hpp
#define Win_hpp

#include <SFML/Graphics.hpp>
#include "ScreenText.hpp"

class Win
{
private:
    sf::Text winText;
    sf::Text restartText;
    
    ScreenText win;
    ScreenText restart;
public:
    Win();
    void render(sf::RenderTarget &target);
};

#endif /* Win_hpp */
