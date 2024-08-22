#ifndef SIMULATION_CLASSES_KEY_H_
#define SIMULATION_CLASSES_KEY_H_

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Key {
public:
	Key(int key);
	Key operator=(Key other);	
	bool operator==(const Key& other) const;
	int GetKey() const;

	void Action(std::function<void(GLFWwindow*, float&)> action, GLFWwindow* window, float& delta_time);	
private:
	int GetState(GLFWwindow* window) const;

	int key_;
	bool pressed_ = false;
};

#endif // SIMULATION_CLASSES_KEY_H_