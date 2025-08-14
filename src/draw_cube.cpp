
#include "draw_cube.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "gl/GLU.h"
#include <vector>
// Vertex structure for cube vertices
struct Vertex {
    float x, y, z;
    float nx, ny, nz; // normals
};

// Function to draw a cube using modern OpenGL approach with vertex arrays
void draw_Cube(float size)
{
    float half = size / 2.0f;

    // Define cube vertices with normals
    std::vector<Vertex> vertices = {
        // Front face (z = half)
        {-half, -half,  half,  0.0f,  0.0f,  1.0f},
        { half, -half,  half,  0.0f,  0.0f,  1.0f},
        { half,  half,  half,  0.0f,  0.0f,  1.0f},
        {-half,  half,  half,  0.0f,  0.0f,  1.0f},

        // Back face (z = -half)
        {-half, -half, -half,  0.0f,  0.0f, -1.0f},
        {-half,  half, -half,  0.0f,  0.0f, -1.0f},
        { half,  half, -half,  0.0f,  0.0f, -1.0f},
        { half, -half, -half,  0.0f,  0.0f, -1.0f},

        // Left face (x = -half)
        {-half, -half, -half, -1.0f,  0.0f,  0.0f},
        {-half, -half,  half, -1.0f,  0.0f,  0.0f},
        {-half,  half,  half, -1.0f,  0.0f,  0.0f},
        {-half,  half, -half, -1.0f,  0.0f,  0.0f},

        // Right face (x = half)
        { half, -half, -half,  1.0f,  0.0f,  0.0f},
        { half,  half, -half,  1.0f,  0.0f,  0.0f},
        { half,  half,  half,  1.0f,  0.0f,  0.0f},
        { half, -half,  half,  1.0f,  0.0f,  0.0f},

        // Top face (y = half)
        {-half,  half, -half,  0.0f,  1.0f,  0.0f},
        {-half,  half,  half,  0.0f,  1.0f,  0.0f},
        { half,  half,  half,  0.0f,  1.0f,  0.0f},
        { half,  half, -half,  0.0f,  1.0f,  0.0f},

        // Bottom face (y = -half)
        {-half, -half, -half,  0.0f, -1.0f,  0.0f},
        { half, -half, -half,  0.0f, -1.0f,  0.0f},
        { half, -half,  half,  0.0f, -1.0f,  0.0f},
        {-half, -half,  half,  0.0f, -1.0f,  0.0f}
    };

    // Define indices for triangles (2 triangles per face)
    std::vector<unsigned int> indices = {
        0,  1,  2,   0,  2,  3,   // Front
        4,  5,  6,   4,  6,  7,   // Back
        8,  9, 10,   8, 10, 11,   // Left
        12, 13, 14,  12, 14, 15,  // Right
        16, 17, 18,  16, 18, 19,  // Top
        20, 21, 22,  20, 22, 23   // Bottom
    };


    glColor3f(.5f, .3f, 0.3f); // White color

    // Draw using immediate mode (legacy OpenGL)
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < indices.size(); i++) {
        const Vertex& v = vertices[indices[i]];
        glNormal3f(v.nx, v.ny, v.nz);
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();
}