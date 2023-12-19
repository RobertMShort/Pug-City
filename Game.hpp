#ifndef Game_hpp
#define Game_hpp

#include "Objects/Pug.hpp"
#include "Ammo/Fire.hpp"
#include "Objects/Building.hpp"
#include "Objects/Plane.hpp"
#include "Ammo/Missle.hpp"
#include "Objects/Tank.hpp"
#include "Ammo/TankBullet.hpp"
#include "Screens/Splash.hpp"
#include "Screens/GameOver.hpp"
#include "Screens/ScreenText.hpp"
#include "Screens/Win.hpp"

#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <memory>

class Game
{
private:
    // Window
    sf::RenderWindow window;
    sf::Event ev;

    // Background
    sf::Texture bgTexture;
    sf::Sprite background;
    
    // Pug
    std::unique_ptr<Pug> pug;
    
    // Pug health bar
    sf::RectangleShape pugHPBar;
    sf::RectangleShape pugHPBarBack;
    
    // Fire
    std::vector<Fire> fireVect;
    sf::Texture fireTexture;

    // Buildings
    sf::Texture buildingTextures[3];
    std::unique_ptr<Building> buildings[3];
    unsigned int BldMaxHitCount;
    
    // Enemy plane
    std::unique_ptr<Plane> plane;
    
    // Enemy plane missles
    std::vector<Missle> missleVect;
    sf::Texture missleTexture;
    unsigned int maxMissles;
    float missleSpawnTimerMax;
    float missleSpawnTimer;
 
    // Enemy tank
    std::unique_ptr<Tank> tank;
    
    // Enemy tank bullets
    std::vector<TankBullet> tankBulletVect;
    sf::Texture tankBulletTexture;
    unsigned int maxTankBullets;
    float tankBulletSpawnTimerMax;
    float tankBulletSpawnTimer;

    // Splash screen
    bool started;
    Splash splash;
    
    // Game Over/restart text
    GameOver gameOver;
    bool endGame;
    
    // Level text
    ScreenText level;
    sf::Text levelText;
    unsigned int levelNum = 0;
    
    // Level 1 instructions
    ScreenText l1;
    sf::Text l1Text;
    
    // Level 2 instructions
    ScreenText l2;
    sf::Text l2Text;
    
    // Level completed
    sf::Text levCompText;
    bool levComp;
    ScreenText levelComp;
    bool showLevelComp = false;
    
    // Points
    sf::Text pointsText;
    ScreenText score;
    
    // Win game
    Win win;
    bool isWin;
    
    // Instructions
    sf::Text instText;
    ScreenText inst;
    
    // Clock/Time
    sf::Clock clock;

    // Private init functions
    void initWindow();
    void initBackground();
    void initBuildingTextures();
    void initVars();
    void initHealthBar();
    void initText();

public:
    Game();
    
    // Accessors
    const bool running() const;
    const bool getEndGame() const;
    
    // Functions
    void pollEvents();
    void shootFire();
    template <class T> void objectHitCount(T& object);
    sf::Vector2f direction(float centerX, float centerY, float posX, float posY);
    void updateFire();
    void updateBuildings();
    void moveAmmo(bool isTank);
    template <class O> void updateEnemyObject(O &object, bool isTank);
    template <class A> void updateAmmo(std::vector<A> &ammoVect, bool tank);
    void updateHealthBar();
    void restart();
    void renderBuildings();
    template <class E> void renderAmmo(std::vector<E> &objectVect, bool isFire);
    void updateFromSplash();
    void startL2();
    void update();
    void render();
};

#endif /* Game_hpp */
