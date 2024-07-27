#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "classes/object.h"
#include "classes/object_shapes.h"
#include "classes/object_handler.h"
#include "classes/settings.h"
#include "classes/glfw_callback.h"
#include "classes/inputs.h"

#define CASE3

int main() {
	// GLFW
	if (!glfwInit()) {
		std::cerr << "glfwInit error" << std::endl;
		return -1;
	}

	// OpenGL (3.1)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	GLFWwindow* window;
	if (Settings::GetInstance().screen_.fullscreen) {
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		window = glfwCreateWindow(mode->width, mode->height, "Simulation", monitor, nullptr);
		Settings::GetInstance().screen_.width = mode->width;
		Settings::GetInstance().screen_.height = mode->height;
		Settings::GetInstance().screen_.koef_screen = static_cast<float>(mode->width) / mode->height;
	} else {
		int width = Settings::GetInstance().screen_.width;
		int height = Settings::GetInstance().screen_.height;
		window = glfwCreateWindow(width, height, "Simulation", nullptr, nullptr);
	}

	if (!window) {
		std::cerr << "glfwCreateWindow error" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Glad" << std::endl;
		glfwTerminate();
		return -1;
	}

	glScalef(1 / Settings::GetInstance().screen_.koef_screen, 1, 1);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glfwSwapInterval(Settings::GetInstance().screen_.vsync);

#ifdef CASE1

	Settings::GetInstance().world_parameters_.gravity = 0.0f;
	Rectangle rect(0, 0, 0, 2.0, 0.15);
	Circle circle0(0, 0.0, 3.5, 0.15);
	Circle circle1(0, -0.5, -0.2, 0.1);
	Circle circle2(0, -0.5, 0.2, 0.1);
	Circle circle3(0, 0.5, -0.2, 0.1);
	circle0.SetVelocity(glm::vec2(0.5f, -3.0f));
	rect.SetAngularVelocity(0.2);

#endif // CASE1

#ifdef CASE2

	Settings::GetInstance().world_parameters_.gravity = 0.0f;
	Settings::GetInstance().world_parameters_.restitution = 1.0f;
	Rectangle floor(1, -2, 0, 0.6f, 2.0f);
	Rectangle floor1(1, 2, 0, 0.6f, 2.0f);
	Rectangle floor2(1, 0, 1.2, 4.0f, 0.6f);
	Rectangle floor3(1, 0, -1.2, 4.0f, 0.6f);
	Circle circle0(0, 0, 0, 0.15);
	Circle circle1(0, -0.5, -0.2, 0.3);
	Circle circle2(0, -0.5, 0.2, 0.15);
	Circle circle3(0, 0.5, -0.2, 0.15);
	Circle circle4(0, -0.1, -0.7, 0.1);
	Circle circle5(0, -0.8, 0.3, 0.15);
	Circle circle6(0, 0.2, -0.1, 0.1);
	circle0.SetVelocity(glm::vec2(3.5f, -1.2f));
	circle2.SetVelocity(glm::vec2(-3.0f, 1.2f));

#endif // CASE2

#ifdef CASE3

	Rectangle floor(1, 0, -1.5f, 6.0f, 2.0f);
	Circle circle0(0, -2, 0.7, 0.4);
	Circle circle1(0, -0.5, 0.3, 0.3);
	Circle circle2(0, 0.7, 0.5, 0.2);
	Circle circle3(0, 1.7, 0.2, 0.1);
	circle0.SetAngularVelocity(-7.0);
	circle2.SetAngularVelocity(4.0);
	circle1.SetVelocity(glm::vec2(0.0, 0));
	circle3.SetAngularVelocity(8.0);

#endif // CASE3

	int fps_counter = 0;

	float last_time = static_cast<float>(glfwGetTime());

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float current_time = static_cast<float>(glfwGetTime());
		float delta_time = current_time - last_time;		
		EdgePan(window, delta_time);
		delta_time *= Settings::GetInstance().world_parameters_.simulation_speed;
		Inputs::GetInstance().CheckInputs(window, delta_time);		
		ObjectHandler::GetInstance().MainCycle(Object::GetObjectsList(), delta_time);

		glfwSwapBuffers(window);
		glfwPollEvents();

		last_time = current_time;
		++fps_counter;
	}

	std::cout << "FPS:\t" << fps_counter / glfwGetTime();
	glfwTerminate();
	return 0;
}
