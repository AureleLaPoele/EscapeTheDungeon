#include "../include/Player.h"
#include "../include/Enemy.h"

Player::Player(int hp, sf::RectangleShape pR, sf::RectangleShape pS, sf::Vector2f p, float s) : hp(hp), playerRect(pR), playerSword(pS), pos(p), speed(s) {
    playerRect.setPosition(pos.x, pos.y);
    float posx = playerRect.getPosition().x + 25.0f;
    float posy = playerRect.getPosition().y + 25.0f;
    playerSword.setPosition(posx, posy);
}

Player::~Player() {
    std::cout << "Le player est détruit\n";
}

void Player::updateTemp(float deltaTime) {

}

void Player::update(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, sf::RenderWindow& window, sf::Time& deltaTime) {
    float dx = 0.0f, dy = 0.0f;

    if (keyStates.at(sf::Keyboard::Z)) {
        dy -= speed;
        //std::cout << "Haut\n";
    }
    if (keyStates.at(sf::Keyboard::S)) {
        dy += speed;
        //std::cout << "Bas\n";
    }
    if (keyStates.at(sf::Keyboard::Q)) {
        dx -= speed;
        //std::cout << "Gauche\n";
    }
    if (keyStates.at(sf::Keyboard::D)) {
        dx += speed;
        //std::cout << "Droite\n";
    }
    if (keyStates.at(sf::Keyboard::Space)) {
        std::cout << "Space\n";
        //for (int i = 0; i < 180; i++) {
        //    playerSword.rotate(1);
        //    sf::sleep(sf::milliseconds(1));
        //    Player::draw(window);
        //    window.draw(playerSword);
        //    std::cout << i << std::endl;
        //}
    }

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }
    playerRect.move(dx * deltaTime.asSeconds(), dy * deltaTime.asSeconds());
    playerSword.move(dx * deltaTime.asSeconds(), dy * deltaTime.asSeconds());
}


void Player::draw(sf::RenderWindow& window) {
    window.draw(playerSword);
    window.draw(playerRect);
}

bool Player::checkCol(sf::RenderWindow& window, sf::RectangleShape& enemyRect) {
    if (playerRect.getGlobalBounds().intersects(enemyRect.getGlobalBounds())) {
        std::cout << "Collision avec enemy\n";
        return true;
    }
    else {
        return false;
    }
}

