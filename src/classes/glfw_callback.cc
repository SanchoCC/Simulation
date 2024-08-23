#include "glfw_callback.h"

#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "settings.h"
#include "object_shapes.h"
#include "key.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	glm::vec2 world_position = GetCursorWorldPosition(window);

	float scale_factor = 1.0f;
	if (yoffset > 0.0) {
		scale_factor = 1.1f; 
	} else if (yoffset < 0.0) {
		scale_factor = 0.9f;
		world_position *= -1;
	}
	float k = 0.1f;
	world_position *= k;
	float modelViewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);

	for (int i = 0; i < std::abs(std::round(yoffset)); ++i) {
		modelViewMatrix[12] -= world_position.x * modelViewMatrix[0] + world_position.y * modelViewMatrix[4];
		modelViewMatrix[13] -= world_position.x * modelViewMatrix[1] + world_position.y * modelViewMatrix[5];

		modelViewMatrix[0] *= scale_factor;
		modelViewMatrix[5] *= scale_factor;
		modelViewMatrix[10] *= scale_factor;
	}

	glLoadMatrixf(modelViewMatrix);
}

void EdgePan(GLFWwindow* window, float& delta_time) {
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);

	double width = Settings::Get().screen_.width;
	double height = Settings::Get().screen_.height;
	double threshold_x = width * 0.1;
	double threshold_y = height * 0.1;
	double threshold_x_closest = width * 0.03;
	double threshold_y_closest = height * 0.03;
	float delta_time_2 = delta_time + delta_time;

	if (x_pos > width - threshold_x_closest) {
		glTranslatef(-delta_time_2, 0, 0);
	} else if (x_pos < threshold_x_closest) {
		glTranslatef(delta_time_2, 0, 0);
	} else if (x_pos > width - threshold_x) {
		glTranslatef(-delta_time, 0, 0);
	} else if (x_pos < threshold_x) {
		glTranslatef(delta_time, 0, 0);
	}
	if (y_pos > height - threshold_y_closest) {
		glTranslatef(0, delta_time_2, 0);
	} else if (y_pos < threshold_y_closest) {
		glTranslatef(0, -delta_time_2, 0);
	} else if (y_pos > height - threshold_y) {
		glTranslatef(0, delta_time, 0);
	} else if (y_pos < threshold_y) {
		glTranslatef(0, -delta_time, 0);
	}
}

glm::vec2 GetCursorWorldPosition(GLFWwindow* window) {
	double x_screen, y_screen;
	glfwGetCursorPos(window, &x_screen, &y_screen);

	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	y_screen = vp[3] - y_screen - 1;

	glm::vec4 viewport = glm::vec4(vp[0], vp[1], vp[2], vp[3]);

	glm::mat4 model, proj;
	glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(model));
	glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(proj));

	glm::vec3 win = glm::vec3(x_screen, y_screen, 1);

	auto UnProject = [](const glm::vec3& win, const glm::mat4& model, const glm::mat4& proj, const glm::vec4& viewport) {
		glm::mat4 inverse = glm::inverse(proj * model);
		glm::vec4 tmp = glm::vec4(win, 1.0);
		tmp.x = (tmp.x - viewport[0]) / viewport[2];
		tmp.y = (tmp.y - viewport[1]) / viewport[3];
		tmp = tmp * 2.0f - 1.0f;

		glm::vec4 obj = inverse * tmp;
		obj /= obj.w;

		return glm::vec3(obj);
	};

	glm::vec3 world_pos = UnProject(win, model, proj, viewport);
	return glm::vec2(world_pos.x, world_pos.y);
}