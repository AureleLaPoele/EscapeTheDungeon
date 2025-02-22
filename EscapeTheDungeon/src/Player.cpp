#include "../include/Player.h"
#include "../include/Enemy.h"
#include "../include/Item.h"

Player::Player(int hp, sf::RectangleShape pR, sf::Vector2f p, float s, float dx, float dy) : hp(hp), playerRect(pR), pos(p), speed(s), dx(dx), dy(dy) {
    playerRect.setPosition(pos.x, pos.y);
    float posx = playerRect.getPosition().x + 25.0f;
    float posy = playerRect.getPosition().y + 25.0f;
}

Player::~Player() {
    std::cout << "Le player est d�truit\n";
}

void Player::updateTemp(float deltaTime) {

}

void Player::update(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, sf::RenderWindow& window, sf::Time& deltaTime, bool speedPotion) {

    if (keyStates.at(sf::Keyboard::Escape)) {
        window.close();
    }
    if (keyStates.at(sf::Keyboard::Z)) {
        dy -= speed;
    }
    if (keyStates.at(sf::Keyboard::S)) {
        dy += speed;
    }
    if (keyStates.at(sf::Keyboard::Q)) {
        dx -= speed;
    }
    if (keyStates.at(sf::Keyboard::D)) {
        dx += speed;
    }

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    if (speedPotion) {
        dx *= 2;
        dy *= 2;
    }

    pos.x += dx * deltaTime.asSeconds();
    pos.y += dy * deltaTime.asSeconds();

    playerRect.move(dx * deltaTime.asSeconds(), dy * deltaTime.asSeconds());
    dx = 0.0f;
    dy = 0.0f;
}


void Player::draw(sf::RenderWindow& window) {
    window.draw(playerRect);
}

bool Player::checkColEnemy(sf::Sprite& enemySprite, int& hp, sf::RectangleShape& playerRect) {
    if (playerRect.getGlobalBounds().intersects(enemySprite.getGlobalBounds())) {
        while (true) {
            float distLeft = playerRect.getPosition().x + playerRect.getSize().x - enemySprite.getPosition().x;
            float distRight = enemySprite.getPosition().x + 32 - playerRect.getPosition().x;
            float distTop = playerRect.getPosition().y + playerRect.getSize().y - enemySprite.getPosition().y;
            float distBottom = enemySprite.getPosition().y + 32 - playerRect.getPosition().y;
            if (distLeft < distRight && distLeft < distTop && distLeft < distBottom) {
                playerRect.move(-32, 0);
            }
            else if (distRight < distLeft && distRight < distTop && distRight < distBottom) {
                playerRect.move(32, 0);
            }
            else if (distTop < distLeft && distTop < distRight && distTop < distBottom) {
                playerRect.move(0, -32);
            }
            else if (distBottom < distLeft && distBottom < distRight && distBottom < distTop) {
                playerRect.move(0, 32);
            }
            break;
        }
        hp -= 25;
        return true;
    }
    else {
        return false;
    }
}

bool Player::checkColItem(sf::RectangleShape& itemRect) {
    if (playerRect.getGlobalBounds().intersects(itemRect.getGlobalBounds())) {
        std::cout << "Collision avec un objet\n";
        return true;
    }
    else {
        return false;
    }
}
