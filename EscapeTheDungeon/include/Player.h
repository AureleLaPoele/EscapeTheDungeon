#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

class Player : public Entity {
public:
    sf::RectangleShape playerRect;
    sf::Vector2f pos;
    float speed;

    Player(sf::RectangleShape pR, sf::Vector2f p, float s);
    ~Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void move(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, const sf::RenderWindow& window);
};

#endif // PLAYER_H
