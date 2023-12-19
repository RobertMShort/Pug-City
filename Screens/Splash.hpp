#ifndef Splash_hpp
#define Splash_hpp

#include <SFML/Graphics.hpp>
#include "ScreenText.hpp"

class Splash
{
private:
    sf::Text splashText;
    sf::Text enterToPlayText;
    sf::Texture pugSplashTexture;
    sf::Sprite pugSplash;
    
    ScreenText splash;
    ScreenText enter;
public:
    Splash();
    void initPugSplash();
    
    void render(sf::RenderTarget &target);
};

#endif /* Splash_hpp */
