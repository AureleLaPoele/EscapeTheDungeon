#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy : public Entity {
public:
    sf::RectangleShape enemyRect;
    sf::Vector2f pos;
    float speed;

    Enemy(sf::RectangleShape pR, sf::Vector2f p, float s);
    ~Enemy();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void ChaserEnemyPattern(const sf::RenderWindow& window, Player& player);
    void PatrollingEnemyPattern(const sf::RenderWindow& window);
    void move(const sf::RenderWindow& window);
};

#endif