#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

class Map {
private:
    std::vector<std::vector<int>> grid;
    int tileSize;

public:
    Map(const std::string& filename, int tileSize) : tileSize(tileSize) {
        loadFromFile(filename);
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
                if (c == '1') row.push_back(1); // Mur
                else if (c == '0') row.push_back(0); // Espace vide
            }
            grid.push_back(row);
        }
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape wall(sf::Vector2f(tileSize, tileSize));
        wall.setFillColor(sf::Color::Blue);

        for (size_t y = 0; y < grid.size(); ++y) {
            for (size_t x = 0; x < grid[y].size(); ++x) {
                if (grid[y][x] == 1) {
                    wall.setPosition(x * tileSize, y * tileSize);
                    window.draw(wall);
                }
            }
        }
    }

    bool isColliding(const sf::FloatRect& bounds) const {
        int leftTile = bounds.left / tileSize;
        int rightTile = (bounds.left + bounds.width) / tileSize;
        int topTile = bounds.top / tileSize;
        int bottomTile = (bounds.top + bounds.height) / tileSize;

        for (int y = topTile; y <= bottomTile; ++y) {
            for (int x = leftTile; x <= rightTile; ++x) {
                if (y >= 0 && y < static_cast<int>(grid.size()) &&
                    x >= 0 && x < static_cast<int>(grid[y].size()) &&
                    grid[y][x] == 1) {
                    return true;
                }
            }
        }
        return false;
    }
};