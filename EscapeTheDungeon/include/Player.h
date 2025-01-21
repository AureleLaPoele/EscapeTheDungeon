#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <unordered_map>

class Player : public Entity {
public:
    int hp;
    sf::RectangleShape playerRect;
    sf::RectangleShape playerSword;
    sf::Vector2f pos;
    float speed;

    Player(int hp, sf::RectangleShape pR, sf::RectangleShape pS, sf::Vector2f p, float s);
    ~Player();

    void updateTemp(float deltaTime) override;
    void update(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, sf::RenderWindow& window, sf::Time& deltaTime, bool speedPotion);
    void draw(sf::RenderWindow& window) override;
    bool checkColEnemy(sf::RectangleShape& enemyRect);
    bool checkColItem(sf::RectangleShape& itemRect);

};

#endif // PLAYER_H
