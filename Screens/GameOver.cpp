#include "GameOver.hpp"

GameOver::GameOver()
{
    this->gameOver.initText(this->gameOverText, 90, sf::Color::Red, 400.f, 400.f);
    this->gameOver.updateText("Game Over", this->gameOverText);
    
    this->restart.initText(this->restartText, 75, sf::Color::White, 375.f, 500.f);
    this->restart.updateText("Restart? : Y/N", this->restartText);
}

void GameOver::render(sf::RenderTarget &target)
{
    target.draw(this->gameOverText);
    target.draw(this->restartText);
}
