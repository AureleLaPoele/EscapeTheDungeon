#include "../include/Enemy.h"

Enemy::Enemy(sf::RectangleShape pR, sf::Vector2f p, float s)
    : enemyRect(pR), pos(p), speed(s) {
    enemyRect.setPosition(pos.x, pos.y);
}

Enemy::~Enemy() {
    std::cout << "L'ennemi est détruit\n";
}

void Enemy::update(float deltaTime) {
    // Cette fonction peut être utilisée pour gérer la mise à jour du joueur à chaque frame
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemyRect);
}

void Enemy::ChaserEnemyPattern(const sf::RenderWindow& window, Player& player) {

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
