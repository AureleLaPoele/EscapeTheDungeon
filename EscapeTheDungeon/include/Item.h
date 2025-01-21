#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Item : public Entity {
public:
	sf::RectangleShape itemRect;
	sf::Vector2f pos;
	std::string type;

	Item(sf::RectangleShape iR, sf::Vector2f p, std::string t);
	~Item();

	virtual void updateTemp(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
};

#endif