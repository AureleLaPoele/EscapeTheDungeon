#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <Windows.h>
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/Item.h"

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
            if (player->checkColEnemy(enemy->enemyRect, player->hp, player->playerRect, player->playerSword)) {
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



//int main() {
//    using namespace std::chrono;
//
//    // Durée du cooldown en secondes
//    const float cooldownTime = 5.0f;
//
//    // Moment de la dernière action, initialisé à un moment passé
//    steady_clock::time_point lastActionTime = steady_clock::now() - seconds(int(cooldownTime));
//
//    while (true) {
//        // Demander à l'utilisateur d'appuyer sur une touche pour effectuer l'action
//        std::cout << "Appuie sur 'Enter' pour effectuer une action (ou 'q' pour quitter)..." << std::endl;
//
//        char input;
//        std::cin >> input;
//
//        if (input == 'q') {
//            break; // Quitte la boucle si l'utilisateur appuie sur 'q'
//        }
//
//        steady_clock::time_point currentTime = steady_clock::now();
//
//        // Calculer le temps écoulé depuis la dernière action
//        float elapsedTime = duration<float>(currentTime - lastActionTime).count();
//
//        if (elapsedTime >= cooldownTime) {
//            // Si le cooldown est terminé, on effectue l'action
//            std::cout << "Action effectuée !" << std::endl;
//            // Met à jour le moment de la dernière action
//            lastActionTime = currentTime;
//        }
//        else {
//            // Si le cooldown n'est pas terminé, informer l'utilisateur
//            std::cout << "Attends encore " << (cooldownTime - elapsedTime) << " secondes avant de refaire l'action." << std::endl;
//        }
//
//        // Attendre un peu pour éviter une boucle trop rapide (facultatif)
//        std::this_thread::sleep_for(milliseconds(100));
//    }
//
//    return 0;
//}


