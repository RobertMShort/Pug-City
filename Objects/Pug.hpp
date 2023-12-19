#ifndef Pug_hpp
#define Pug_hpp

#include <SFML/Graphics.hpp>

// PARENT CLASS

class Pug
{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    
    float speed;
    int hitCount;
    
    void initSprite();
    
private:
    int hp;
    int hpMax;
    int score;
    
public:
    Pug();
    
    // Accessors
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    int getHitCount();
    const int& getHP() const;
    const int& getHPMax() const;
    int getScore();
    
    // Modifiers
    void setHP(const int hp);
    void loseHP(const int value);
    void incrementHP(const int inc);
    void resetScore();
    void incrementScore(const int inc);
    
    // Functions
    void movePug(const float dirX);
    void increment();
    
    void update();
    void render(sf::RenderTarget &target);
};

#endif /* Pug_hpp */
