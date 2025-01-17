#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "include/Player.h"

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
    Player* player = new Player(playerRect, sf::Vector2f(200, 300), 10.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Fermer la fenêtre
            }
            if (event.type == sf::Event::KeyPressed) {
                keyStates[event.key.code] = true;
                player->move(keyStates, window);
            }
            if (event.type == sf::Event::KeyReleased) {
                keyStates[event.key.code] = false;
            }
        }

        window.clear();
        player->draw(window);
        window.display();
    }

    delete player;
    return 0;
}
