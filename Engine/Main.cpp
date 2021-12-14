/*******************************************************************
** This code is part of Healthier.
**
** Esse é o trabalho prático 1 da matéria 
** Computação Gráfica - 2021/2 - UFMG
**
** Caio Rocha - 2021421893
******************************************************************/

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "./ResourceManager/ResourceManager.h"
#include "../Game/Game.h"

#include<iostream>

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Base screen size
const unsigned int SCREEN_WIDTH = 600;
const unsigned int SCREEN_HEIGHT = 700;

Game Healthier = Game();

int main() {
	// -------------------- GLFW CONFIG --------------------
	// Initializes GLFW
	glfwInit();
	// Specify the client API (OpenGL) version (in this case 3.3) that 
	// the created context must be compatible
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile (Mordern functions) or Compatibility Profile (Modern + Outdated)
	// Using CORE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Disable resizing
	//glfwWindowHint(GLFW_RESIZABLE, false);
	

	// Making it full screen (windowed full screen)
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Healthier", primary, NULL);
	// Error check
	if (window == NULL) {
		std::cout << "Failed to create GLFW window <<" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Telling glfw that the current context has to be into 'window'
	glfwMakeContextCurrent(window);

	// -------------------- OPENGL CONFIGS --------------------
	
	// Load GLAD so it configures OpenGL function pointers
	gladLoadGL();
	/* Other way
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}*/


	// ------------- GLFW INPUT FUNCTIONS ---------------
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Specifying the OpenGL's viewport inside the window (x1, y1, x2, y2)
	glViewport(0, 0, mode->width, mode->height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// -------------------- GAME CONFIG --------------------
	

	// Initialization
	Healthier.Init(mode->width, mode->height);

	// DeltaTime variables
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Handles the state of the game
		Healthier.ProcessGameState(deltaTime);

		if (Healthier.state == GameState::GAME_CLOSE) {
			glfwSetWindowShouldClose(window, true);
		}

		// Calls for Update in this tick
		Healthier.Update(deltaTime);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Healthier.Render();

		glfwSwapBuffers(window);
	}

	// Deletes all textures and shaders
	ResourceManager::Clear();

	// Ends the window and GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

	// ----------------------------------------------------------
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Healthier.keys[key] = true;
		else if (action == GLFW_RELEASE)
			Healthier.keys[key] = false;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Healthier.SetMousePos(glm::vec2(xpos, ypos));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		Healthier.keys[button] = true;
	else if (action == GLFW_RELEASE)
		Healthier.keys[button] = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}