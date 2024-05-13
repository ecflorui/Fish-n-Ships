#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PerlinNoise.h"

#define WIDTH 100
#define HEIGHT 60
int PERLIN = 1;
int MOUNTAIN = 3;
int LAND = 2;
int BEACH = 1;
int ALIVE = 1;
int DEAD = 0;
int map[HEIGHT][WIDTH];
double pMap[HEIGHT][WIDTH]; //Map for perlin noise
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
    if(PERLIN == 0){
        for(int h = 0; h < HEIGHT; h++) {
            for(int w = 0; w < WIDTH; w++) {
                if(pMap[h][w] == MOUNTAIN) {
                    std::cout << "\033[39m■\033[0m";
                }
                else if(pMap[h][w] == ALIVE) {
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
    if(PERLIN == 1){
        for(int h = 0; h < HEIGHT; h++) {
            for(int w = 0; w < WIDTH; w++) {
                if(pMap[h][w] == MOUNTAIN) {
                    std::cout << "\033[39m■\033[0m";
                }
                else if(pMap[h][w] == LAND) {
                    // Output alive cells in green
                    std::cout << "\033[32m■\033[0m"; // Green color
                } else if(pMap[h][w] == BEACH){
                    std::cout << "\033[33m■\033[0m";
                }
                else {
                    // Output dead cells in blue
                    std::cout << "\033[34m■\033[0m"; // Blue color
                }
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    genCave();
    if(PERLIN == 0){
        for(int gen = 0; gen < generations; gen++) {
            for(int h = 1; h < HEIGHT - 1; h++) {
                for(int w = 1; w < WIDTH - 1; w++) {
                    int count = near(w, h);
                    if(map[h][w] == DEAD && count >= 7) {
                        map[h][w] = MOUNTAIN;
                    }
                    if(map[h][w] == DEAD && count >= 6 && count < 7) {
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
    }
    else{
        PerlinNoise * p = new PerlinNoise(26);
        std::cout << p->noise(.1,.1);
        for(int h = 1; h < HEIGHT - 1; h++) {
            for(int w = 1; w < WIDTH - 1; w++) {
                pMap[h][w] = p->octaveNoise((double)10*h/HEIGHT, (double)10*w/WIDTH,7,.5,1);
                if(pMap[h][w] >= .4) {
                    pMap[h][w] = MOUNTAIN;
                }
                if(pMap[h][w] >= .2 && pMap[h][w] < .4) {
                    pMap[h][w] = LAND;
                }
                if(pMap[h][w] >= .01 && pMap[h][w] < .2) {
                    pMap[h][w] = BEACH;
                }
                if(pMap[h][w] <= .01) {
                    pMap[h][w] = DEAD;
                }
            }
        }
        displayCave();
        std::cout << std::endl;
    }
    return 0;
}
