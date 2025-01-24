#include "../include/Enemy.h"

Enemy::Enemy(sf::RectangleShape pR, sf::Vector2f p, float s, float dx, float dy)
    : enemyRect(pR), pos(p), speed(s), dx(dx), dy(dy) {
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
    float speed = 0.01f;
    if (posx <= enemyRect.getPosition().x) {
        dx = -speed;
    }
    if (posx >= enemyRect.getPosition().x) {
        dx = speed;
    }
    if (posy <= enemyRect.getPosition().y) {
        dy = -speed;
    }
    if (posy >= enemyRect.getPosition().y) {
        dy = speed;
    }
    enemyRect.move(dx, dy);
}

void Enemy::PatrollingEnemyPattern(const sf::RenderWindow& window) {

}

void Enemy::move(const sf::RenderWindow& window) {

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    enemyRect.move(dx, dy);
}
