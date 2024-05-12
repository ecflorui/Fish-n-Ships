#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <cmath>


class PerlinNoise {
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);

    double noise(double x, double y) const;
    double octaveNoise(double x, double y, int octaves, double persistence = 0.5, double scale = 0.1) const;

private:
    std::vector<int> p;
    double fade(double t) const;
    double lerp(double t, double a, double b) const;
    double grad(int hash, double x, double y) const;
};

PerlinNoise::PerlinNoise() {
    // Initialize permutation vector with values 0..255
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);

    // Shuffle permutation vector using seed 0
    std::default_random_engine engine(0);
    std::shuffle(p.begin(), p.end(), engine);

    // Duplicate permutation vector to avoid buffer overflow
    p.insert(p.end(), p.begin(), p.end());
}

PerlinNoise::PerlinNoise(unsigned int seed) {
    // Initialize permutation vector with values 0..255
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);

    // Shuffle permutation vector using given seed
    std::default_random_engine engine(seed);
    std::shuffle(p.begin(), p.end(), engine);

    // Duplicate permutation vector to avoid buffer overflow
    p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::noise(double x, double y) const {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    double u = fade(x);
    double v = fade(y);

    int A = p[X] + Y;
    int AA = p[A];
    int AB = p[A + 1];
    int B = p[X + 1] + Y;
    int BA = p[B];
    int BB = p[B + 1];

    return lerp(v, lerp(u, grad(p[AA], x, y), grad(p[BA], x - 1, y)),
                   lerp(u, grad(p[AB], x, y - 1), grad(p[BB], x - 1, y - 1)));
}

double PerlinNoise::octaveNoise(double x, double y, int octaves, double persistence, double scale) const {
    double total = 0.0;
    double frequency = scale;
    double amplitude = 1.0;
    double maxValue = 0.0;

    for (int i = 0; i < octaves; ++i) {
        total += noise(x * frequency, y * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2.0;
    }

    return total / maxValue;
}

double PerlinNoise::fade(double t) const {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) const {
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y) const {
    int h = hash & 7;
    double u = h < 4 ? x : y;
    double v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
}
