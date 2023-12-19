#ifndef TankBullet_hpp
#define TankBullet_hpp

#include "Missle.hpp"

class TankBullet : public Missle
{
public:
    TankBullet(sf::Texture &texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed);
};

#endif /* TankBullet_hpp */
