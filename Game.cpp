#include "Game.hpp"

// Initializers
void Game::initWindow()
{
    window.create(sf::VideoMode(1200, 800), "Pug City", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
}

void Game::initBackground()
{
    bgTexture.loadFromFile("assets/city.png");
    background.setTexture(bgTexture);
    background.setPosition(0, 0);
    background.setScale(1.5f, 1.5f);
}

void Game::initBuildingTextures()
{
    buildingTextures[0].loadFromFile("assets/building.png");
    buildingTextures[1].loadFromFile("assets/building2.png");
    buildingTextures[2].loadFromFile("assets/building3.png");
}

void Game::initVars()
{
    maxMissles = 5;
    missleSpawnTimerMax = 10.f;
    missleSpawnTimer = missleSpawnTimerMax;
    
    maxTankBullets = 5;
    tankBulletSpawnTimerMax = 10.f;
    tankBulletSpawnTimer = tankBulletSpawnTimerMax;
    
    BldMaxHitCount = 20; // Change back to 200
    
    pug = std::make_unique<Pug>();
    plane = std::make_unique<Plane>();
    buildings[0] = std::make_unique<Building>(buildingTextures[0], 575.f, levelNum == 2 ? 800.f : 449.f, 0.4f, 0.4f);
    buildings[1] = std::make_unique<Building>(buildingTextures[1], 710.f, levelNum == 2 ? 800.f : 449.f, 0.4f, 0.4f);
    buildings[2] = std::make_unique<Building>(buildingTextures[2], 940.f, levelNum == 2 ? 800.f : 449.f, 0.3f, 0.3f);
    tank = std::make_unique<Tank>();
    
    started = false;
    endGame = false;
    levComp = false;
    isWin = false;
}

void Game::initHealthBar()
{
    pugHPBar.setSize(sf::Vector2f(300.f, 25.f));
    pugHPBar.setFillColor(sf::Color::Red);
    pugHPBar.setPosition(sf::Vector2f(20.f, 20.f));

    pugHPBarBack = pugHPBar;
    pugHPBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initText()
{
    // Points
    score.initText(pointsText, 50, sf::Color::Black, 525.f, 5.f);
    // Level completed
    levelComp.initText(levCompText, 75, sf::Color::Red, 400.f, 200.f);
    // Level 1 instructions
    l1.initText(l1Text, 50, sf::Color::Black, 325.f, 200.f);
    // Level2 instructions
    l2.initText(l2Text, 50, sf::Color::Black, 325.f, 200.f);
    // Level text
    level.initText(levelText, 40, sf::Color::White, 20.f, 55.f);
    // Instructions
    inst.initText(instText, 35, sf::Color::Yellow, 20.f, 600.f);
}

// Constructor/Deconstructor
Game::Game()
{
    initWindow();
    initBackground();
    initBuildingTextures();
    initVars();
    initHealthBar();
    initText();
    
    fireTexture.loadFromFile("assets/fire2.png");
    missleTexture.loadFromFile("assets/missle.png");
    tankBulletTexture.loadFromFile("assets/tankBullet.png");
}

// Accessors
const bool Game::running() const
{
    return window.isOpen();
}

const bool Game::getEndGame() const
{
    return endGame;
}

// Functions
void Game::pollEvents()
{
    while (window.pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();
                
                // Restart or quit if out of health
                if (pug->getHP() <= 0 || isWin == true) {
                        if (ev.key.code == sf::Keyboard::Y)
                            restart();
                        if (ev.key.code == sf::Keyboard::N)
                            endGame = true;
                }
                break;
            default:
                break;
        }
    }
}

void Game::shootFire()
{
    if (sf::Event::MouseButtonPressed)
    {
        if (ev.mouseButton.button == sf::Mouse::Left && ev.type != sf::Event::MouseButtonReleased)
            
            if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < window.getSize().x && sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < window.getSize().y) {
                fireVect.push_back(Fire(fireTexture, pug->getPos().x + 5.f + 300, pug->getPos().y + 5.f,
                                        this->direction((pug->getPos().x + 5.f) + 320, pug->getPos().y + 5.f, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y).x, this->direction((pug->getPos().x + 5.f) + 320, pug->getPos().y + 5.f, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y).y,
                                              5.f));
            }
    }
}

template <class T> void Game::objectHitCount(T &object)
{
    unsigned counter = 0;
    for (Fire fire : fireVect)
    {
        if (fire.getBounds().intersects(object->getBounds())) {
            object->increment();
            object->update();
            fireVect.erase(fireVect.begin() + counter);
            --counter;
        }
        ++counter;
    }
    
    if (object->getHitCount() == BldMaxHitCount) {
        pug->incrementScore(25);
        pug->incrementHP(25);
    }
}

sf::Vector2f Game::direction(float centerX, float centerY, float posX, float posY)
{
    sf::Vector2f playerCenter(centerX, centerY);
    sf::Vector2f Position(posX, posY);
    sf::Vector2f aimDir(Position - playerCenter);
    sf::Vector2f aimDirNorm(aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
    sf::Vector2f currVelocity(aimDirNorm * 2.f);
    
    return currVelocity;
}

void Game::updateFire()
{
    unsigned counter = 0;
    for (Fire &fire : fireVect) {
        fire.update();
        if (fire.getBounds().left + fire.getBounds().width > 1200 || fire.getBounds().top + fire.getBounds().height < 0) {
            fireVect.erase(fireVect.begin() + counter);
            --counter;
        }
        ++counter;
    }
}

void Game::updateBuildings()
{
    for (int i = 0; i < 3; i++) {
        if (buildings[i]->getHitCount() < BldMaxHitCount) {
            if (buildings[i]->getPos().y <= 449)
                objectHitCount(buildings[i]);
            buildings[i]->move();
        }
    }
    
    // Level 1
    if (levelNum == 1) {
        if (buildings[0]->getHitCount() >= BldMaxHitCount && buildings[1]->getHitCount() >= BldMaxHitCount && buildings[2]->getHitCount() >= BldMaxHitCount) {
            levComp = true;
            showLevelComp = true;
        }
    }
    
    // Level 2
    if (levelNum == 2) {
        if (buildings[0]->getHitCount() >= BldMaxHitCount) {
            buildings[0] = std::make_unique<Building>(buildingTextures[0], 575.f, 800.f, 0.4f, 0.4f);
        } else if (buildings[1]->getHitCount() >= BldMaxHitCount) {
            buildings[1] = std::make_unique<Building>(buildingTextures[1], 710.f, 800.f, 0.4f, 0.4f);
        } else if (buildings[2]->getHitCount() >= BldMaxHitCount) {
            buildings[2] = std::make_unique<Building>(buildingTextures[2], 940.f, 800.f, 0.3f, 0.3f);
        }
    }
    
    // Level 2
    if (this->clock.getElapsedTime().asSeconds() > 5) {
        if (buildings[0]->getPos().y >= 750 && buildings[1]->getPos().y >= 750 && buildings[2]->getPos().y >= 750) {
            levComp = true;
            this->isWin = true;
        }
    }
}

template <class A> void Game::updateAmmo(std::vector<A> &ammoVect, bool tank)
{
    unsigned counter = 0;
    for (auto &i : ammoVect) {
        i.update();
        if (i.getBounds().intersects(pug->getBounds())) {
            pug->increment();
            pug->update();
            
            if (tank == true) {
                tankBulletVect.erase(tankBulletVect.begin() + counter);
            }
            else {
                missleVect.erase(missleVect.begin() + counter);
            }
            --counter;
            pug->loseHP(1);
        }
        ++counter;
    }
}

void Game::moveAmmo(bool isTank)
{
   if (isTank == true)
   {
       if (tankBulletVect.size() < maxTankBullets && tank->getPos().x <= 500 && tank->getHitCount() < 100)
       {
           if (tankBulletSpawnTimer >= tankBulletSpawnTimerMax) {
               tankBulletVect.push_back(TankBullet(tankBulletTexture, tank->getPos().x, tank->getPos().y + 10,
                                                   this->direction(tank->getPos().x, tank->getPos().y, pug->getPos().x + 320, pug->getPos().y).x, this->direction(tank->getPos().x, tank->getPos().y, pug->getPos().x + 320, pug->getPos().y + 120).y,
                                                 1.f));
               tankBulletSpawnTimer = 0.f;
           }
           else
               tankBulletSpawnTimer += 0.5f;
       }
   }
    else
    {
        if (missleVect.size() < maxMissles && plane->getPos().x <= 500 && plane->getHitCount() < 100)
        {
            if (missleSpawnTimer >= missleSpawnTimerMax) {
                missleVect.push_back(Missle(missleTexture, plane->getPos().x, plane->getPos().y + 100,
                                            this->direction(plane->getPos().x, plane->getPos().y, pug->getPos().x + 150, pug->getPos().y).x, this->direction(plane->getPos().x, plane->getPos().y, pug->getPos().x + 150, pug->getPos().y).y,
                                                  1.f));
                missleSpawnTimer = 0.f;
            }
            else
                missleSpawnTimer += 0.5f;
        }
    }
}

template <class O> void Game::updateEnemyObject(O &object, bool isTank)
{
    if (object->getHitCount() < 100) {
        object->move();
        this->objectHitCount(object);
    }
    else {
        if (isTank == true) {
            tank = std::make_unique<Tank>();
        }
        else {
            plane = std::make_unique<Plane>();
        }

        pug->incrementScore(10);
        pug->incrementHP(10);
    }
}

void Game::updateHealthBar()
{
    float hpPercent = static_cast<float>(this->pug->getHP()) / pug->getHPMax();
    pugHPBar.setSize(sf::Vector2f(300.f * hpPercent, pugHPBar.getSize().y));
}

void Game::restart()
{
    initVars();
    started = true;
    levelNum = 1;
    
    this->clock.restart();
    
    missleVect.clear();
    tankBulletVect.clear();
    fireVect.clear();
}

void Game::renderBuildings()
{
    for (int i = 0; i < 3; i++) {
        if (buildings[i]->getHitCount() < BldMaxHitCount) {
            buildings[i]->render(window);
        }
    }
}

template <class E> void Game::renderAmmo(std::vector<E> &objectVect, bool isFire)
{
    for (auto &i : objectVect) {
        if (isFire == false) {
            i.update();
        }
        i.render(window);
    }
}

void Game::updateFromSplash()
{
    if (sf::Event::KeyPressed) {
        if (started == false) {
            if (ev.key.code == sf::Keyboard::Enter) {
                l1.updateText("Level 1: Destroy all the buildings.\n\nPress Y to continue...", l1Text);
                inst.updateText("Instructions:\nLeft mouse button to shoot.", instText);
                levelNum = 1;
            }
        }
        
            if (sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::Y) {
                    started = true;
                }
            }
    }
}

void Game::startL2()
{
    if (sf::Event::KeyPressed) {
        if (levComp == true) {
            if (showLevelComp == true)
                levelComp.updateText("Level Complete\n\nPress Y to continue", levCompText);
            
            if (this->ev.key.code == sf::Keyboard::Y) {
                showLevelComp = false;
                levelNum = 2;
                level.updateText("Level " + std::to_string(levelNum), levelText);
                l2.updateText("Level 2: Keep all the buildings destroyed.\n\nPress Enter to start", l2Text);
            }
            
            if (ev.key.code == sf::Keyboard::Enter) {
                restart();
                levelNum = 2;
            }
        }
    }
}

void Game::update()
{
    pollEvents();

    updateFromSplash();
    startL2();
    
    // Start game
    if (started == true && levComp == false){
        shootFire();
        updateFire();
        updateBuildings();
        
        // Plane and missles
        updateEnemyObject(plane, false);
        moveAmmo(false);
        updateAmmo(missleVect, false);
        
        // Tank and bullets
        updateEnemyObject(tank, true);
        moveAmmo(true);
        updateAmmo(tankBulletVect, true);

        updateHealthBar();
        
        // Points
        score.updateText("Score: " + std::to_string(pug->getScore()), pointsText);
        
        // Level
        level.updateText("Level " + std::to_string(levelNum), levelText);
    }
}

void Game::render()
{
    window.clear();
    
    window.draw(background);
    
    if (started == true) {
        pug->render(window);
        
        // Fire
        if (pug->getHP() > 0) {
            renderAmmo(fireVect, true);
        }
        
        renderBuildings();
        
        // Plane and Missles
        plane->render(window);
        renderAmmo(this->missleVect, false);
        
        // Tank and Bullets
        tank->render(window);
        renderAmmo(tankBulletVect, false);
        
        // Pug health bar
        window.draw(pugHPBarBack);
        window.draw(pugHPBar);
        
        // Points
        score.render(window, pointsText);
        
        // Level
        level.render(window, levelText);
        
        // Game Over text
        if (pug->getHP() <= 0) {
            gameOver.render(window);
        }
        
        // Win
        if (this->isWin == true) {
            this->win.render(window);
        }
        
        // Level completed
        if (showLevelComp == true) {
            levelComp.render(window, levCompText);
        }
        
        // Level 2
        if (levelNum == 2 && levComp == true && isWin == false)
            l2.render(window, l2Text);
    } else {
        // Splash screen
        if (levelNum == 0 && started == false)
            splash.render(window);
        
        // Level 1
        if (levelNum == 1) {
            l1.render(window, l1Text);
            inst.render(window, instText);
        }
        
    }

    window.display();
}
