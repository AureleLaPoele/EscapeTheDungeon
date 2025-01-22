#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/Item.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

std::unordered_map<sf::Keyboard::Key, bool> keyStates = {
    {sf::Keyboard::Z, false},
    {sf::Keyboard::S, false},
    {sf::Keyboard::Q, false},
    {sf::Keyboard::D, false},
    {sf::Keyboard::Space, false}
};



int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Escape The Dungeon");

    sf::RectangleShape playerRect(sf::Vector2f(50, 50));
    playerRect.setFillColor(sf::Color::Green);
    sf::RectangleShape playerSword(sf::Vector2f(50, 5));
    playerSword.rotate(-90);
    sf::RectangleShape enemyRect(sf::Vector2f(50, 50));
    enemyRect.setFillColor(sf::Color::Red);
    sf::RectangleShape itemRect(sf::Vector2f(50, 50));
    itemRect.setFillColor(sf::Color::Blue);

    std::vector<Enemy*> enemies;
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 200), 3.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 300), 3.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 400), 3.0f));
    Enemy* chaser = new Enemy(enemyRect, sf::Vector2f(300, 200), 1.0f);
    Player* player = new Player(100, playerRect, playerSword, sf::Vector2f(200, 300), 300.0f);
    Item* item = new Item(itemRect, sf::Vector2f(200, 200), "speedPotion");

    float speed = 2.0f;
    sf::Clock clock;

    bool speedPotion = false;

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

        for (auto& enemy : enemies) {
            if (player->checkColEnemy(enemy->enemyRect)) {
                player->hp -= 25;
                player->playerRect.move(-100, 0);
                player->playerSword.move(-100, 0);
            }
        }
        player->checkColEnemy(chaser->enemyRect);

        if (player->checkColItem(item->itemRect)) {
            speedPotion = true;
        }
        if (player->hp <= 0) {
            return 0;
        }

        player->update(keyStates, window, deltaTime, speedPotion);

        window.clear();
        for (auto& enemy : enemies) {
            enemy->move(window);
            enemy->draw(window);
        }
        chaser->ChaserEnemyPattern(player->pos.x, player->pos.y);
        player->draw(window);
        chaser->draw(window);
        item->draw(window);
        window.display();
    }
    for (auto& enemy : enemies) {
        delete enemy;
    }
    delete chaser;
    delete item;
    delete player;
    return 0;
}
