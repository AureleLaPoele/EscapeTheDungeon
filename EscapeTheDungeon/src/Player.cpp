#include "../include/Player.h"

Player::Player(sf::RectangleShape pR, sf::Vector2f p, float s)
    : playerRect(pR), pos(p), speed(s) {
    playerRect.setPosition(pos.x, pos.y);
}

Player::~Player() {
    std::cout << "Le player est d�truit\n";
}

void Player::update(float deltaTime) {
    // Cette fonction peut �tre utilis�e pour g�rer la mise � jour du joueur � chaque frame
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(playerRect);
}

void Player::move(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, const sf::RenderWindow& window) {
    float dx = 0.0f, dy = 0.0f;

    if (keyStates.at(sf::Keyboard::Z)) {
        dy -= speed;
        std::cout << "Haut\n";
    }
    if (keyStates.at(sf::Keyboard::S)) {
        dy += speed;
        std::cout << "Bas\n";
    }
    if (keyStates.at(sf::Keyboard::Q)) {
        dx -= speed;
        std::cout << "Gauche\n";
    }
    if (keyStates.at(sf::Keyboard::D)) {
        dx += speed;
        std::cout << "Droite\n";
    }

    // Diagonal correction pour �viter un d�placement plus rapide en diagonale
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    playerRect.move(dx, dy);
}
