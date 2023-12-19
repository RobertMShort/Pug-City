#include "Win.hpp"

Win::Win()
{
    this->win.initText(this->winText, 90, sf::Color::Red, 400.f, 400.f);
    this->win.updateText("YOU WIN!", this->winText);
    
    this->restart.initText(this->restartText, 75, sf::Color::White, 375.f, 500.f);
    this->restart.updateText("Play again? : Y/N", this->restartText);
}

void Win::render(sf::RenderTarget &target)
{
    target.draw(this->winText);
    target.draw(this->restartText);
}
