#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:

    virtual void updateTemp(float deltaTime) = 0;  // Méthode virtuelle pure
    virtual void draw(sf::RenderWindow& window) = 0;  // Méthode virtuelle pure
    virtual ~Entity() {}
};

#endif // ENTITY_H
