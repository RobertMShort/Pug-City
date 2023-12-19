#ifndef Fire_hpp
#define Fire_hpp

#include <SFML/Graphics.hpp>

// PARENT CLASS 

class Fire
{
protected:
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;
    
public:
    Fire(sf::Texture &texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed);
    
    // Accessor
    const sf::FloatRect getBounds() const;
    
    // Functions
    void update();
    void render(sf::RenderTarget &target);
};

#endif /* Fire_hpp */
