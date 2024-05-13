#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>

class PerlinNoise {
  public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    double noise(double x, double y) const;
    double octaveNoise(double x, double y, int octaves, double persistence, double scale) const;

private:
std::vector<int> p;
double fade(double t) const;
double lerp(double t, double a, double b) const;
double grad(int hash, double x, double y) const;
};

#endif