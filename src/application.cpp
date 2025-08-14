#include "application.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "gl/GLU.h"

// Example usage with GLFW
Application::Application(): clipPlane(1., 0., 0., 0.) {
	initOpenGL();
}

Application::~Application() {
	glfwTerminate();
}



void enablePolygonStippling()
{
	GLubyte pattern[] = {
				0,   0,  0,  0,  255,  255,  255,  255,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  255,  255,  255,  255,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
				0,   0,  0,  0,  0,  0,  0,  0,
	};

	glEnable(GL_POLYGON_STIPPLE);
	glColor3f(0.f, 0.f, 0.f);
	glPolygonStipple(pattern);
	glDepthFunc(GL_LEQUAL);
}
// Function to draw the cap surface
void drawCap() {

	const float Ymax = 2.0f, Zmax = 3.0f;

	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
		{
			glColor3f(0.f, 1.f, 0.f); // green color
			glDepthFunc(GL_LESS);
		}
		else
		{
			glPolygonOffset(2.0, 2.0);
			enablePolygonStippling(); // color will be set to black
		}

		glDisable(GL_CULL_FACE); 

		// Draw a quad at the clip plane position
		glNormal3f(1.0f, 0.0f, 0.0f);  // Normal pointing in +x direction

		glBegin(GL_POLYGON);

		glVertex3f(0.0f, -Ymax, -Zmax);
		glVertex3f(0.0f, -Ymax, Zmax);
		glVertex3f(0.0f, Ymax, Zmax);
		glVertex3f(0.0f, Ymax, -Zmax);
		glEnd();

	}

	glDisable(GL_POLYGON_STIPPLE);

}

// Function to draw a cube with proper normals
void drawCube() {
	glBegin(GL_QUADS);

	// Front face (z = 1.0)
	glNormal3f(0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// Back face (z = -1.0)
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Left face (x = -1.0)
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Right face (x = 1.0)
	glNormal3f(1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Top face (y = 1.0)
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Bottom face (y = -1.0)
	glNormal3f(0.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);  // Red
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();
}

// Setup lighting
void setupLighting() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { 3.0f, 3.0f, 3.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}


void enable_stencil_testing()
{
	glClearStencil(0);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
	glEnable(GL_STENCIL_TEST);
}

void apply_stencil_buffer()
{
	glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void reset_stencil_buffer()
{
	glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
	glDisable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_STENCIL_BUFFER_BIT);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_C:
			app->enableClipping = !app->enableClipping;
			std::cout << "Clipping " << (app->enableClipping ? "enabled" : "disabled") << std::endl;
			break;
		case GLFW_KEY_X:
			if (mods & GLFW_MOD_SHIFT) {
				app->rotationX -= 5.0f;
			}
			else {
				app->rotationX += 5.0f;
			}
			break;
		case GLFW_KEY_Y:
			if (mods & GLFW_MOD_SHIFT) {
				app->rotationY -= 5.0f;
			}
			else {
				app->rotationY += 5.0f;
			}
			break;
		case GLFW_KEY_R:
			app->rotationX = app->rotationY = 0.0f;
			std::cout << "Rotation reset" << std::endl;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		}
	}
}


// Mouse button callback
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {


	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			app->mousePressed = true;
			glfwGetCursorPos(window, &app->lastMouseX, &app->lastMouseY);
		}
		else if (action == GLFW_RELEASE) {
			app->mousePressed = false;
		}
	}
}

// Mouse movement callback
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app->mousePressed) {
		double deltaX = xpos - app->lastMouseX;
		double deltaY = ypos - app->lastMouseY;

		app->rotationY += deltaX * 0.5f;
		app->rotationX += deltaY * 0.5f;

		app->lastMouseX = xpos;
		app->lastMouseY = ypos;
	}
}

// Window resize callback
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	app->windowWidth = width;
	app->windowHeight = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
}
// Error callback
void errorCallback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}


void Application::initOpenGL() {

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasing
	glfwWindowHint(GLFW_STENCIL_BITS, 8);  // Request stencil buffer

	window = glfwCreateWindow(windowWidth, windowHeight, "cutplane_mesa", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);


	// Enable v-sync
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window, this);

	// Set callbacks
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


	glfwSetErrorCallback(errorCallback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	std::cout << "OpenGL " << GLVersion.major << ", " << GLVersion.minor << std::endl;

	const GLubyte* vendor = glGetString(GL_VENDOR);
	std::cout << "OpenGL Vendor: " << vendor << "\n";


	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);  // gray background
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	// Enable smooth shading
	glShadeModel(GL_SMOOTH);

	// Enable back face culling for better performance
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Set up initial projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)windowWidth / (double)windowHeight, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
}


void Application::enableClipPlane()
{
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, clipPlane.equation);
}

// Render the complete scene with clipping and capping
void Application::render_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Position camera
	gluLookAt(4.0, 3.0, 6.0,    // Eye position
		0.0, 0.0, 0.0,    // Look at center
		0.0, 1.0, 0.0);   // Up vector

	// Apply rotations
	glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

	setupLighting();

	if(enableClipping)
	{
		enableClipPlane();
		enable_stencil_testing();
	}
	else
	{
		glDisable(GL_CLIP_PLANE0);
	}
	drawCube();

	if (enableClipping)
	{
		glDisable(GL_CLIP_PLANE0);
		apply_stencil_buffer();
		drawCap();
		reset_stencil_buffer();
	}
}

void Application::run() {

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		render_scene();
		glfwSwapBuffers(window);
	}
}
