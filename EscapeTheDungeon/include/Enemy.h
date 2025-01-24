#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy : public Entity {
public:
    sf::Sprite enemySprite;
    sf::Vector2f pos;
    float speed;
    float dx;
    float dy;

    Enemy(sf::Sprite eS, sf::Vector2f p, float s, float dx, float dy);
    ~Enemy();

    void updateTemp(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void ChaserEnemyPattern(float posx, float posy);
    void PatrollingEnemyPattern(const sf::RenderWindow& window);
    void move(const sf::RenderWindow& window);
};

#endif