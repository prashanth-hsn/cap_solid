#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>


// Clip plane structure
struct ClipPlane {
    double equation[4];  // ax + by + cz + d = 0

    ClipPlane(double a, double b, double c, double d) {
        equation[0] = a;
        equation[1] = b;
        equation[2] = c;
        equation[3] = d;
    }
};


// Example usage with GLFW
class Application {

public:
    Application();

    ~Application();

    void run();

    double rotationX = {}, rotationY = {};
    double lastMouseX = {}, lastMouseY = {};
    bool enableClipping = false;
    bool mousePressed = false;

    int windowWidth = 800;
    int windowHeight = 600;
private:
    // Global clip plane - cuts through middle of cube
    ClipPlane clipPlane;

    void initOpenGL();
    void render_scene();
    void enableClipPlane();

    GLFWwindow* window;

}; 
