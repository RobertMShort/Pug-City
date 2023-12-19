#ifndef Tank_hpp
#define Tank_hpp

#include "Plane.hpp"

class Tank : public Plane
{
private:
    void initSprite();
public:
    Tank();
    void render(sf::RenderTarget &target);
};

#endif /* Tank_hpp */
