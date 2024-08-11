#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

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
	if (Settings::Get().screen_.fullscreen) {
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		window = glfwCreateWindow(mode->width, mode->height, "Simulation", monitor, nullptr);
		Settings::Get().screen_.width = mode->width;
		Settings::Get().screen_.height = mode->height;
		Settings::Get().screen_.koef_screen = static_cast<float>(mode->width) / mode->height;
	} else {
		int width = Settings::Get().screen_.width;
		int height = Settings::Get().screen_.height;
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

	glScalef(1 / Settings::Get().screen_.koef_screen, 1, 1);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glfwSwapInterval(Settings::Get().screen_.vsync);

#ifdef CASE1

	Settings::GetInstance().world_parameters_.gravity = 0.0f;
	Rectangle rect(0, 0, 2.0, 0.15, MaterialType::kMetal);
	rect.SetAngularVelocity(0.2);

	Circle circle0(0.0, 3.5, 0.2, MaterialType::kRock);
	circle0.SetVelocity(glm::vec2(0.3f, -2.f));

	Circle circle1(-0.5, -0.2, 0.1, MaterialType::kDefault);

	Circle circle2(-0.5, 0.2, 0.1, MaterialType::kWood);

	Circle circle3(0.5, -0.2, 0.1, MaterialType::kRubber);
#endif // CASE1

#ifdef CASE2

	Settings::GetInstance().world_parameters_.gravity = 0.0f;
	Rectangle floor(-2, 0, 0.6f, 2.0f, MaterialType::kRubber);
	floor.SetStatical(true);
	Rectangle floor1(2, 0, 0.6f, 2.0f, MaterialType::kRubber);
	floor1.SetStatical(true);
	Rectangle floor2(0, 1.2, 4.0f, 0.6f, MaterialType::kRubber);
	floor2.SetStatical(true);
	Rectangle floor3(0, -1.2, 4.0f, 0.6f, MaterialType::kRubber);
	floor3.SetStatical(true);
	
	Circle circle0(0, 0, 0.2, MaterialType::kMetal);
	circle0.SetVelocity(glm::vec2(1.5f, -1.2f));
	Circle circle1(-0.5, -0.2, 0.3, MaterialType::kRubber);
	Circle circle2(-0.5, 0.2, 0.2, MaterialType::kMetal);
	circle2.SetVelocity(glm::vec2(2.0f, 1.5f));
	Circle circle3(0.5, -0.2, 0.15, MaterialType::kRubber);
	Circle circle4(-0.1, -0.7, 0.1, MaterialType::kRubber);
	Circle circle5(-0.8, 0.3, 0.15, MaterialType::kRubber);
	Circle circle6(0.2, -0.1, 0.1, MaterialType::kRubber);	

#endif // CASE2

#ifdef CASE3

	Rectangle floor(0, -1.5f, 6.0f, 2.0f, MaterialType::kIce);
	floor.SetStatical(true);
	Circle circle0(-2, 0.7, 0.4, MaterialType::kWood);
	Circle circle1(-0.5, 0.3, 0.3, MaterialType::kIce);
	Circle circle2(0.7, 0.5, 0.2, MaterialType::kIce);
	Circle circle3(1.7, 0.2, 0.1, MaterialType::kIce);
	circle0.SetAngularVelocity(-7.0);
	circle1.SetVelocity(glm::vec2(0.0, 0));
	circle2.SetAngularVelocity(4.0);
	circle3.SetAngularVelocity(8.0);

#endif // CASE3

#ifdef CASE4

	Rectangle floor00(0, -1.f, 8.0f, 1.0f, MaterialType::kDefault);
	floor00.SetStatical(true);
	floor00.SetRotationAngle(-0.25);
	Circle circle00(-1.5, 0.3, 0.3, MaterialType::kRubber);
	circle00.SetAngularVelocity(5.0);

	Circle circle01(-0.5, 0.2, 0.3, MaterialType::kRock);
	circle01.SetAngularVelocity(5.0);

	Circle circle02(0.5, 0.1, 0.3, MaterialType::kMetal);
	circle02.SetAngularVelocity(5.0);

	Circle circle03(1.5, 0.0, 0.3, MaterialType::kIce);
	circle03.SetAngularVelocity(5.0);		

	Rectangle floor10(0, 3.f, 8.0f, 1.0f, MaterialType::kIce);
	floor10.SetStatical(true);
	floor10.SetRotationAngle(-0.25);
	Circle circle10(-1.5, 4.3, 0.3, MaterialType::kMetal);
	circle10.SetAngularVelocity(5.0);

	Circle circle11(-0.5, 4.2, 0.3, MaterialType::kIce);
	circle11.SetAngularVelocity(5.0);

	Circle circle12(0.5, 4.1, 0.3, MaterialType::kMetal);
	circle12.SetAngularVelocity(5.0);

	Circle circle13(1.5, 4.0, 0.3, MaterialType::kIce);
	circle13.SetAngularVelocity(5.0);

	glScalef(0.3f, 0.3f, 1);
	glTranslatef(0, -1.2f, 0);

#endif // CASE4

	int fps_counter = 0;

	float last_time = static_cast<float>(glfwGetTime());
	glm::mat4 origin(1.f);
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		float current_time = static_cast<float>(glfwGetTime());
		float delta_time = current_time - last_time;		
		EdgePan(window, delta_time);
		
		Inputs::Get().CheckInputs(window, delta_time);		
		delta_time *= Settings::Get().world_parameters_.simulation_speed;

		ObjectHandler::Get().MainCycle(Object::GetObjectsList(), delta_time);

		glfwSwapBuffers(window);
		glfwPollEvents();

		last_time = current_time;
		++fps_counter;
	}

	std::cout << "FPS:\t" << fps_counter / glfwGetTime();
	glfwTerminate();
	return 0;
}
