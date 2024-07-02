#include "glfw_callback.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "settings.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0.0) {
		for (int i = 0; i < std::round(yoffset); ++i) {
			glScalef(1.1, 1.1, 0);
		}
	} else if (yoffset < 0.0) {
		for (int i = 0; i < std::abs(std::round(yoffset)); ++i) {
			glScalef(0.9, 0.9, 0);
		}
	}
}

void EdgePan(GLFWwindow* window) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	double width = Settings::GetInstance().screen_.width;
	double height = Settings::GetInstance().screen_.height;
	double threshold_x = width * 0.12;
	double threshold_y = height * 0.12;
	double threshold_x_closest = width * 0.02;
	double threshold_y_closest = height * 0.02;

	if (xpos > width - threshold_x_closest) {
		glTranslatef(-Settings::GetInstance().state_.delta_time * 2, 0, 0);
	} else if (xpos < 0.0 + threshold_x_closest) {
		glTranslatef(Settings::GetInstance().state_.delta_time * 2, 0, 0);
	} else if (xpos > width - threshold_x) {
		glTranslatef(-Settings::GetInstance().state_.delta_time, 0, 0);
	} else if (xpos < 0.0 + threshold_x) {
		glTranslatef(Settings::GetInstance().state_.delta_time, 0, 0);
	}
	if (ypos > height - threshold_y_closest) {
		glTranslatef(0, Settings::GetInstance().state_.delta_time * 2, 0);
	} else if (ypos < 0.0 + threshold_y_closest) {
		glTranslatef(0, -Settings::GetInstance().state_.delta_time * 2, 0);
	} else if (ypos > height - threshold_y) {
		glTranslatef(0, Settings::GetInstance().state_.delta_time, 0);
	} else if (ypos < 0.0 + threshold_y) {
		glTranslatef(0, -Settings::GetInstance().state_.delta_time, 0);
	}	
}

