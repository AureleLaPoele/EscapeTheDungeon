#include "../include/Item.h"

Item::Item(sf::RectangleShape iR, sf::Vector2f p, std::string t) : itemRect(iR), pos(p), type(t) {
    itemRect.setPosition(pos.x, pos.y);
    std::cout << "L'item " << type << " est construit\n";
}

Item::~Item() {
    std::cout << "L'item " << type << " est détruit\n";
}

void Item::updateTemp(float deltaTime) {

}

void Item::draw(sf::RenderWindow& window) {
    window.draw(itemRect);
}