#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <Windows.h>
#include "src/Map.cpp"
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/Item.h"
#include "include/Sword.h"

const int WIDTH = 1024;
const int HEIGHT = 768;

WORD GetTextAttribute() {
    auto info = CONSOLE_SCREEN_BUFFER_INFO();
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.wAttributes;
}

std::unordered_map<sf::Keyboard::Key, bool> keyStates = {
    {sf::Keyboard::Escape, false},
    {sf::Keyboard::Z, false},
    {sf::Keyboard::S, false},
    {sf::Keyboard::Q, false},
    {sf::Keyboard::D, false},
    {sf::Keyboard::Space, false}
};

int main() {
    WORD oldAttr = GetTextAttribute();

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Escape The Dungeon");
    Map map("map.txt", 32);

    sf::RectangleShape playerRect(sf::Vector2f(32, 32));
    playerRect.setFillColor(sf::Color::Green);
    sf::RectangleShape swordRect(sf::Vector2f(32, 5));
    swordRect.rotate(-90);
    sf::RectangleShape enemyRect(sf::Vector2f(32, 32));
    enemyRect.setFillColor(sf::Color::Red);
    sf::RectangleShape itemRect(sf::Vector2f(32, 32));
    itemRect.setFillColor(sf::Color::Blue);

    std::vector<Enemy*> enemies;
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 200), 3.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 300), 3.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(700, 400), 3.0f));
    Enemy* chaser = new Enemy(enemyRect, sf::Vector2f(300, 200), 1.0f);
    Player* player = new Player(100, playerRect, swordRect, sf::Vector2f(200, 300), 300.0f);
    Item* speedPotion = new Item(itemRect, sf::Vector2f(200, 200), "speedPotion");

    float speed = 2.0f;
    sf::Clock clock;

    bool speedPotionEffect = false;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        window.clear();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                keyStates[event.key.code] = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                keyStates[event.key.code] = false;
            }
        }

        /*player->checkColEnemy(chaser->enemyRect);*/

        if (player->hp <= 0) {
            std::cout << "GAME OVER";
            return 0;
        }

        if (speedPotion != nullptr) {
            if (player->checkColItem(speedPotion->itemRect)) {
                speedPotionEffect = true;
                if (speedPotion) {
                    delete speedPotion;
                    speedPotion = nullptr;
                }
            }
        }

        player->update(keyStates, window, deltaTime, speedPotionEffect);

        for (auto& enemy : enemies) {
            /*enemy->move(window);*/
            enemy->draw(window);
            if (player->checkColEnemy(enemy->enemyRect, player->hp, player->playerRect)) {
                std::cout << "Le joueur a ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
                std::cout << player->hp;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                std::cout << " de points de vie\n";
            }

        }

        chaser->ChaserEnemyPattern(player->pos.x, player->pos.y);
        player->draw(window);
        chaser->draw(window);
        map.draw(window);
        if (speedPotion != nullptr) {
            speedPotion->draw(window);
        }
        window.display();
    }
    for (auto& enemy : enemies) {
        delete enemy;
    }
    delete chaser;
    delete speedPotion;
    delete player;
    return 0;
}



