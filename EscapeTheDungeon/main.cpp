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
    WORD oldAttr = GetTextAttribute(); // Changer la couleur de l'output dans ma console

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Escape The Dungeon");
    Map* room1 = new Map("room1.txt", 32);              // Room 1 normal
    Map* room1open = new Map("room1open.txt", 32);      // Room 1 mais avec le côté gauche ouvert pour aller à la fin du jeu

    sf::RectangleShape playerRect(sf::Vector2f(32, 32));
    playerRect.setFillColor(sf::Color::Green);
    sf::RectangleShape enemyRect(sf::Vector2f(32, 32));
    enemyRect.setFillColor(sf::Color::Red);
    sf::RectangleShape speedPotionRect(sf::Vector2f(32, 32));
    speedPotionRect.setFillColor(sf::Color::Blue);
    sf::RectangleShape keyRect(sf::Vector2f(32, 32));
    keyRect.setFillColor(sf::Color::Magenta);

    std::vector<Enemy*> enemies;
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(864, 604), 3.0f, -0.1f, 0.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(128, 668), 3.0f, 0.1f, 0.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(128, 64), 3.0f, 0.1f, 0.0f));
    enemies.push_back(new Enemy(enemyRect, sf::Vector2f(864, 128), 3.0f, -0.1f, 0.0f));
    Enemy* chaser = new Enemy(enemyRect, sf::Vector2f(300, 200), 1.0f, 0.0f, 0.0f);
    Player* player = new Player(100, playerRect, sf::Vector2f(96, 288), 300.0f, 0.0f, 0.0f);
    Item* speedPotion = new Item(speedPotionRect, sf::Vector2f(96, 352), "speedPotion");
    Item* key1 = new Item(keyRect, sf::Vector2f(64, 636), "key1");
    Item* key2 = new Item(keyRect, sf::Vector2f(960, 96), "key2");

    float speed = 2.0f;
    sf::Clock clock;

    bool speedPotionEffect = false;
    bool key1Collected = false;
    bool key2collected = false;
    int room = 1;

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

        if (room == 1) {
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

            if (key1 != nullptr) {
                if (player->checkColItem(key1->itemRect)) {
                    key1Collected = true;
                    if (key1) {
                        delete key1;
                        key1 = nullptr;
                    }
                }
            }

            if (key2 != nullptr) {
                if (player->checkColItem(key2->itemRect)) {
                    key2collected = true;
                    if (key2) {
                        delete key2;
                        key2 = nullptr;
                    }
                }
            }

            sf::Vector2f movement(player->dx, player->dy);
            sf::FloatRect nextPosition = player->playerRect.getGlobalBounds();
            nextPosition.left += movement.x;
            nextPosition.top += movement.y;

            CollisionDirection collision = room1->getCollisionDirection(nextPosition);

            if (collision == CollisionDirection::None) {
                player->update(keyStates, window, deltaTime, speedPotionEffect);
            }
            else {
                switch (collision) {
                case CollisionDirection::Right:
                    player->playerRect.move(-32, 0);
                    player->pos.x -= 32;
                    std::cout << "Droite\n";;
                    break;
                case CollisionDirection::Left:
                    player->playerRect.move(32, 0);
                    player->pos.x += 32;
                    std::cout << "Gauche\n";
                    break;
                case CollisionDirection::Top:
                    player->playerRect.move(0, 32);
                    player->pos.y += 32;
                    std::cout << "Haut\n";
                    break;
                case CollisionDirection::Bottom:
                    player->playerRect.move(0, -32);
                    player->pos.y -= 32;
                    std::cout << "Bas\n";
                    break;
                default:
                    break;
                }
            }

            for (auto& enemy : enemies) {
                sf::Vector2f movement(enemy->dx, enemy->dy);
                sf::FloatRect nextPosition = enemy->enemyRect.getGlobalBounds();
                nextPosition.left += movement.x;
                nextPosition.top += movement.y;
                CollisionDirection collision = room1->getCollisionDirection(nextPosition);
                if (collision == CollisionDirection::None) {
                    enemy->move(window);
                }
                else {
                    switch (collision) {
                    case CollisionDirection::Right:
                        enemy->dx = -0.1f;
                        break;
                    case CollisionDirection::Left:
                        enemy->dx = 0.1f;
                        break;
                    default:
                        break;
                    }
                }
                enemy->draw(window);
                if (player->checkColEnemy(enemy->enemyRect, player->hp, player->playerRect)) {
                    std::cout << "Le joueur a ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
                    std::cout << player->hp;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
                    std::cout << " de points de vie\n";
                    player->playerRect.setPosition(96, 288);
                }

            }

            /*chaser->ChaserEnemyPattern(player->pos.x, player->pos.y);*/

            //std::cout << player->pos.x << " " << player->pos.y << std::endl;
        }
        player->draw(window);
        chaser->draw(window);
        if (speedPotion != nullptr) {
            speedPotion->draw(window);
        }
        if (key1 != nullptr) {
            key1->draw(window);
        }
        if (key2 != nullptr) {
            key2->draw(window);
        }
        if (!key1Collected && !key2collected) {
            room1->draw(window);
        }
        else {
            room1open->draw(window);
        }
        window.display();
    }
        
    for (auto& enemy : enemies) {
        delete enemy;
    }
    if (speedPotion != nullptr) {
        delete speedPotion;
    }
    if (key1 != nullptr) {
        delete key1;
    }
    if (key2 != nullptr) {
        delete key2;
    }
    delete chaser;
    delete player;
    delete room1;
    delete room1open;
    return 0;
}



