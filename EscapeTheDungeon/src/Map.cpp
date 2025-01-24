#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

enum class CollisionDirection {
    None,
    Left,
    Right,
    Top,
    Bottom
};

class Map {
public:
    std::vector<std::vector<int>> grid;
    sf::Texture wallTexture;
    sf::Sprite wallSprite;
    int tileSize;

    Map(const std::string& filename, int tileSize) : tileSize(tileSize) {
        loadFromFile(filename);
        if (!wallTexture.loadFromFile("wall.png")) {
            throw std::runtime_error("Failed to load wall texture!");
        }
        wallSprite.setTexture(wallTexture);
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open map file!");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (char c : line) {
                if (c == '1') row.push_back(1);
                else if (c == '0') row.push_back(0);
            }
            grid.push_back(row);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x] == 1) {
                    wallSprite.setPosition(x * tileSize, y * tileSize);
                    window.draw(wallSprite);
                }
            }
        }
    }

    CollisionDirection getCollisionDirection(const sf::FloatRect& bounds) const {
        int leftTile = bounds.left / tileSize;
        int rightTile = (bounds.left + bounds.width) / tileSize;
        int topTile = bounds.top / tileSize;
        int bottomTile = (bounds.top + bounds.height) / tileSize;

        for (int y = topTile; y <= bottomTile; ++y) {
            for (int x = leftTile; x <= rightTile; ++x) {
                if (y >= 0 && y < static_cast<int>(grid.size()) &&
                    x >= 0 && x < static_cast<int>(grid[y].size()) &&
                    grid[y][x] == 1) {
                    if (bounds.left + bounds.width > x * tileSize && bounds.left < (x + 1) * tileSize) {
                        if (bounds.top < (y + 1) * tileSize && bounds.top + bounds.height > y * tileSize) {
                            float overlapLeft = (bounds.left + bounds.width) - (x * tileSize);
                            float overlapRight = ((x + 1) * tileSize) - bounds.left;
                            float overlapTop = (bounds.top + bounds.height) - (y * tileSize);
                            float overlapBottom = ((y + 1) * tileSize) - bounds.top;

                            if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
                                return CollisionDirection::Right;
                            }
                            else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
                                return CollisionDirection::Left;
                            }
                            else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom) {
                                return CollisionDirection::Bottom;
                            }
                            else {
                                return CollisionDirection::Top;
                            }
                        }
                    }
                }
            }
        }
        return CollisionDirection::None;
    }
};