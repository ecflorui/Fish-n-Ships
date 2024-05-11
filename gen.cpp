#include <iostream>
#include <cstdlib>
#include <ctime>

#define WIDTH 100
#define HEIGHT 60
int ALIVE = 1;
int DEAD = 0;
int map[HEIGHT][WIDTH];
int seed = std::time(nullptr); // Using std::time(nullptr) to get current time as seed

int aliveProb = 58;
int generations = 1; // Increased number of generations for more iterations

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
        for(int dw = -1; dw <= 1; dw++) {
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

void displayCave() {
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            if(map[h][w]) {
                // Output alive cells in green
                std::cout << "\033[32m■\033[0m"; // Green color
            } else {
                // Output dead cells in blue
                std::cout << "\033[34m□\033[0m"; // Blue color
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    genCave();
    for(int gen = 0; gen < generations; gen++) {
        for(int h = 1; h < HEIGHT - 1; h++) {
            for(int w = 1; w < WIDTH - 1; w++) {
                int count = near(w, h);
                if(map[h][w] == DEAD && count >= 6) {
                    map[h][w] = ALIVE;
                }
                if(map[h][w] == ALIVE && count <= 3) {
                    map[h][w] = DEAD;
                }
            }
        }
        displayCave();
        std::cout << std::endl;
    }
    return 0;
}
