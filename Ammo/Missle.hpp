#ifndef Missle_hpp
#define Missle_hpp

#include "Fire.hpp"

class Missle : public Fire
{
public:
    Missle(sf::Texture &texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed);
    const sf::Vector2f& getPos() const;

};

#endif /* Missle_hpp */
