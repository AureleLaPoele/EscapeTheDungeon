#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "include/Player.h"
#include "include/Enemy.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

std::unordered_map<sf::Keyboard::Key, bool> keyStates = {
    {sf::Keyboard::Z, false},
    {sf::Keyboard::S, false},
    {sf::Keyboard::Q, false},
    {sf::Keyboard::D, false},
    {sf::Keyboard::Space, false}
};


bool checkCol(sf::RenderWindow* window, sf::RectangleShape* playerRect, std::vector<Enemy*>* enemies);

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Escape The Dungeon");

    sf::RectangleShape playerRect(sf::Vector2f(50, 50));
    playerRect.setFillColor(sf::Color::Green);
    sf::RectangleShape enemyRect(sf::Vector2f(50, 50));
    enemyRect.setFillColor(sf::Color::Red);

    std::vector<Enemy*> enemies;
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 200), 3.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 300), 3.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 400), 3.0f));
    Player* player = new Player(playerRect, sf::Vector2f(200, 300), 300.0f);

    enemies[0]->enemyRect;
    float speed = 2.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Fermer la fenêtre
            }
            if (event.type == sf::Event::KeyPressed) {
                keyStates[event.key.code] = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                keyStates[event.key.code] = false;
            }
        }

        /*checkCol(window, playerRect, enemies);*/
        player->move(keyStates, window, deltaTime);

        window.clear();
        for (auto& enemy : enemies) {
            enemy->draw(window);
            enemy->move(window);
        }
        player->draw(window);
        window.display();
    }
    for (auto& enemy : enemies) {
        delete enemy;
    }
    delete player;
    return 0;
}

bool checkCol(sf::RenderWindow* window, sf::RectangleShape* playerRect, std::vector<Enemy*>* enemies) {
    /*for (auto& enemy : *enemies) {
        if (playerRect->getGlobalBounds().intersects(enemyRect->getGlobalBounds())) {
            std::cout << "Collision entre un enemy et le player\n";
        }
        std::cout << enemy << std::endl;
    }*/

    std::cout << "test\n";
}