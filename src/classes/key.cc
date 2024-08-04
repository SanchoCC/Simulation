#include "key.h"

Key::Key(int key) {
	key_ = key;
}

Key Key::operator=(Key other) {
	return other;
}

bool Key::operator==(const Key& other) const {
	return key_ == other.key_;
}

int Key::GetState(GLFWwindow* window) const {
	return glfwGetKey(window, key_);
}

int Key::GetKey() const {
	return key_;
}

void Key::Action(std::function<void(GLFWwindow*, float&)> action, GLFWwindow* window, float& delta_time) {
	int state = GetState(window);
	if (!pressed_ && state == GLFW_PRESS) {
		action(window, delta_time); 
		pressed_ = true;
	} else if (pressed_ && state == GLFW_RELEASE) {
		pressed_ = false;
	}
}