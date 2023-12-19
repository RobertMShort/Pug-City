#ifndef Plane_hpp
#define Plane_hpp

#include "Pug.hpp"

class Plane : public Pug
{
protected:
    void initSprite();
    
public:
    Plane();
    void move();
    void update();
    void render(sf::RenderTarget &target);

};

#endif /* Plane_hpp */
