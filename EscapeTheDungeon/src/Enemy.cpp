#include "../include/Enemy.h"

Enemy::Enemy(sf::RectangleShape pR, sf::Vector2f p, float s)
    : enemyRect(pR), pos(p), speed(s) {
    enemyRect.setPosition(pos.x, pos.y);
}

Enemy::~Enemy() {
    std::cout << "L'ennemi est détruit\n";
}

void Enemy::updateTemp(float deltaTime) {
    // Cette fonction peut être utilisée pour gérer la mise à jour du joueur à chaque frame
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemyRect);
}

void Enemy::ChaserEnemyPattern(float posx, float posy) {
    float dx = 0.0f;
    float dy = 0.0f;
    std::cout << "posx du player : " << posx << std::endl;
    std::cout << "posy du player : " << posy << std::endl;
    std::cout << "posx de l'enemy : " << enemyRect.getPosition().x << std::endl;
    std::cout << "posy de l'enemy : " << enemyRect.getPosition().y << std::endl;
    //if (enemyRect.getPosition().x > posx) {
    //    dx = 0.01f;
    //}
    if (enemyRect.getPosition().x < posx) {
        dx = -0.01f;
    }
    //if (enemyRect.getPosition().y > posy) {
    //    dy = 0.01f;
    //}
    if (enemyRect.getPosition().y < posx) {
        dy = -0.01f;
    }
    enemyRect.move(dx, dy);
}

void Enemy::PatrollingEnemyPattern(const sf::RenderWindow& window) {

}

void Enemy::move(const sf::RenderWindow& window) {
    float dx = -0.01f, dy = 0.0f;

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    enemyRect.move(dx, dy);
}
