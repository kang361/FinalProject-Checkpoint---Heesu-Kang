// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <iostream>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 10;

class GameOfLife {
public:
    GameOfLife(sf::RenderWindow& window) : window(window) {
        initializeGrid();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow& window;
    sf::RectangleShape cellShape;
    std::vector<std::vector<bool>> grid;

    void initializeGrid() {
        for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
            std::vector<bool> row;
            for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
                row.push_back(rand() % 2 == 0);
            }
            grid.push_back(row);
        }

        cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    int countNeighbors(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!(i == 0 && j == 0) && x + i >= 0 && x + i < WIDTH / CELL_SIZE && y + j >= 0 && y + j < HEIGHT / CELL_SIZE) {
                    count += grid[x + i][y + j] ? 1 : 0;
                }
            }
        }
        return count;
    }

    void update() {
        std::vector<std::vector<bool>> newGrid = grid;

        for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
            for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
                int neighbors = countNeighbors(i, j);

                if (grid[i][j]) { // Cell is alive
                    if (neighbors < 2 || neighbors > 3) {
                        // Rule 1 and Rule 3: Die
                        newGrid[i][j] = false;
                    }
                    // Rule 2: Live on
                }
                else { // Cell is dead
                    if (neighbors == 3) {
                        // Rule 4: Become alive
                        newGrid[i][j] = true;
                    }
                }
            }
        }

        grid = newGrid;
    }

    void render() {
        window.clear();

        for (int i = 0; i < WIDTH / CELL_SIZE; ++i) {
            for (int j = 0; j < HEIGHT / CELL_SIZE; ++j) {
                cellShape.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                cellShape.setFillColor(grid[i][j] ? sf::Color::White : sf::Color::Black);
                window.draw(cellShape);
            }
        }

        window.display();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life");
    GameOfLife game(window);
    game.run();

    return 0;
}
