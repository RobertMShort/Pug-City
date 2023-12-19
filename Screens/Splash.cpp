#include "Splash.hpp"

Splash::Splash()
{
    this->initPugSplash();
    
    this->splash.initText(this->splashText, 150, sf::Color::Black, 375.f, 200.f);
    this->splash.updateText("Pug City", this->splashText);
    
    this->enter.initText(this->enterToPlayText, 75, sf::Color::White, 425.f, 350.f);
    this->enter.updateText("Press Enter", this->enterToPlayText);
}

void Splash::initPugSplash()
{
    this->pugSplashTexture.loadFromFile("assets/pugSplash.png");
    this->pugSplash.setTexture(pugSplashTexture);
    this->pugSplash.setPosition(270, 220);
    this->pugSplash.setScale(0.1f, 0.1f);
}

void Splash::render(sf::RenderTarget &target)
{
    target.draw(this->splashText);
    target.draw(this->enterToPlayText);
    target.draw(this->pugSplash);
}
