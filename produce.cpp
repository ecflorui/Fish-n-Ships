#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define WIDTH 200
#define HEIGHT 120
int ALIVE = 1;
int DEAD = 0;
int map[HEIGHT][WIDTH];
int seed = std::time(nullptr);

int aliveProb = 58;
int generations = 1;

void genCave() {
    std::srand(seed);
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            map[h][w] = (std::rand() % 100 > aliveProb) ? DEAD : ALIVE;
        }
    }
}

int near(int x, int y) {
    int count = 0;
    for(int dh = -1; dh <= 1; dh++) {
        for(int dw = -1; dw <= t1; dw++) {
            if(!(dw == 0 && dh == 0)) {
                int nh = y + dh;
                int nw = x + dw;
                if(nh >= 0 && nh < HEIGHT && nw >= 0 && nw < WIDTH) {
                    count += map[nh][nw];
                }
            }
        }
    }
    return count;
}

void updateMap() {
    int newMap[HEIGHT][WIDTH];
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            int count = near(w, h);
            if(map[h][w] == DEAD && count >= 6) {
                newMap[h][w] = ALIVE;
            }
            else if(map[h][w] == ALIVE && count <= 3) {
                newMap[h][w] = DEAD;
            }
            else {
                newMap[h][w] = map[h][w];
            }
        }
    }
    // Update the map
    std::memcpy(map, newMap, sizeof(map));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH * 4, HEIGHT * 4), "Cellular Automata");
    window.setFramerateLimit(10); // Limit frame rate to 10 FPS for visualization

    genCave();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateMap();

        window.clear();

        // Draw cells based on the map
        for (int h = 0; h < HEIGHT; h++) {
            for (int w = 0; w < WIDTH; w++) {
                sf::RectangleShape cell(sf::Vector2f(4.f, 4.f)); // Larger cell size
                cell.setPosition(w * 4.f, h * 4.f); // Position each cell in the grid
                if (map[h][w] == ALIVE) {
                    cell.setFillColor(sf::Color::Green); // Alive cells are green
                } else {
                    cell.setFillColor(sf::Color::Blue); // Dead cells are blue
                }
                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}
