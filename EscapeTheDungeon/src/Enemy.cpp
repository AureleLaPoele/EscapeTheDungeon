#include "../include/Enemy.h"

Enemy::Enemy(sf::RectangleShape pR, sf::Vector2f p, float s)
    : enemyRect(pR), pos(p), speed(s) {
    enemyRect.setPosition(pos.x, pos.y);
}

Enemy::~Enemy() {
    std::cout << "L'ennemi est d�truit\n";
}

void Enemy::updateTemp(float deltaTime) {
    // Cette fonction peut �tre utilis�e pour g�rer la mise � jour du joueur � chaque frame
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemyRect);
}

void Enemy::ChaserEnemyPattern(float posx, float posy) {
    float dx = 0.0f;
    float dy = 0.0f;
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
    float dx = -0.01f, dy = 0.0f;

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    enemyRect.move(dx, dy);
}
