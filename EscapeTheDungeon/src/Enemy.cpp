#include "../include/Enemy.h"

Enemy::Enemy(sf::RectangleShape pR, sf::Vector2f p, float s)
    : enemyRect(pR), pos(p), speed(s) {
    enemyRect.setPosition(pos.x, pos.y);
}

Enemy::~Enemy() {
    std::cout << "L'ennemi est d�truit\n";
}

void Enemy::update(float deltaTime) {
    // Cette fonction peut �tre utilis�e pour g�rer la mise � jour du joueur � chaque frame
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemyRect);
}

void Enemy::move(const sf::RenderWindow& window) {
    float dx = -0.01f, dy = 0.0f;

    // Diagonal correction pour �viter un d�placement plus rapide en diagonale
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    enemyRect.move(dx, dy);
}
