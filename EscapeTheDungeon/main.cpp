#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

const int WIDTH = 1024;
const int HEIGHT = 768;

std::unordered_map<sf::Keyboard::Key, bool> keyStates = {
	{sf::Keyboard::Z, false},
	{sf::Keyboard::S, false},
	{sf::Keyboard::Q, false},
	{sf::Keyboard::D, false},
	{sf::Keyboard::Space, false}
};

class Entity {
public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

class Player : public Entity {
public:
	sf::RectangleShape playerRect;
	sf::Vector2f pos;
	float speed;

	Player(sf::RectangleShape pR, sf::Vector2f p, float s) : playerRect(pR), pos(p), speed(s) {
		playerRect.setPosition(pos.x, pos.y);
	}
	~Player() {
		std::cout << "Le player est détruit";
	}

	void update(float deltaTime) override {

	}

	void draw(sf::RenderWindow& window) override {
		window.draw(playerRect);
	}

	void move(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, const sf::RenderWindow& window) {
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

		if (dx != 0 && dy != 0) {
			dx *= 0.7071f;
			dy *= 0.7071f;
		}

		playerRect.move(dx, dy);
	}
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