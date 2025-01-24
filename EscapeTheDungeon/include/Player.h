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
    sf::Vector2f pos;
    float speed;
    float dx;
    float dy;

    Player(int hp, sf::RectangleShape pR, sf::Vector2f p, float s, float dx, float dy);
    ~Player();

    void updateTemp(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void update(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, sf::RenderWindow& window, sf::Time& deltaTime, bool speedPotion);
    bool checkColEnemy(sf::RectangleShape& enemyRect, int& hp, sf::RectangleShape& playerRect);
    bool checkColItem(sf::RectangleShape& itemRect);

};

#endif // PLAYER_H
