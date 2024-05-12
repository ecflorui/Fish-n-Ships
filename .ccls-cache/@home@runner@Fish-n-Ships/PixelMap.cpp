#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "PerlinNoise.h"

PerlinNoise perlin;  // Initialize Perlin noise generator

// Function to draw the Perlin noise visualization
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a 2D grid of points with Perlin noise values
    glBegin(GL_POINTS);
    for (int y = 0; y < 600; ++y) {
        for (int x = 0; x < 800; ++x) {
            double n = perlin.noise(x / 100.0, y / 100.0); // Adjust the divisor for different noise scale
            glColor3d(n, n, n);  // Set color based on noise value (grayscale)
            glVertex2i(x, y);  // Draw a point at (x, y)
        }
    }
    glEnd();

    glFlush();  // Flush the OpenGL pipeline
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set clear color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0); // Set the 2D coordinate system
}

int main() {
    GLFWwindow* window;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialization failed\n";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "Perlin Noise", NULL, NULL);
    if (!window) {
        std::cerr << "Error: GLFW window creation failed\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set up OpenGL settings
    init();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        display();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up GLFW resources
    glfwTerminate();

    return 0;
}
