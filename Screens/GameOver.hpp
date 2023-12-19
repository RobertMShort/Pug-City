#ifndef GameOver_hpp
#define GameOver_hpp

#include <SFML/Graphics.hpp>
#include "ScreenText.hpp"

class GameOver
{
private:
    sf::Text gameOverText;
    sf::Text restartText;
    
    ScreenText gameOver;
    ScreenText restart;
public:
    GameOver();
    void render(sf::RenderTarget &target);
};

#endif /* GameOver_hpp */
