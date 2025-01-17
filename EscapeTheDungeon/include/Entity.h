#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void update(float deltaTime) = 0;  // M�thode virtuelle pure
    virtual void draw(sf::RenderWindow& window) = 0;  // M�thode virtuelle pure
    virtual ~Entity() {}
};

#endif // ENTITY_H
