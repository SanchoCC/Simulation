#ifndef SIMULATION_CLASSES_KEY_H_
#define SIMULATION_CLASSES_KEY_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

class Key {
public:
	Key(int key);
	Key operator=(Key other);	
	bool Key::operator==(const Key& other) const;
	int GetKey() const;

	void Action(std::function<void(GLFWwindow*, float&)> action, GLFWwindow* window, float& delta_time);	
private:
	int GetState(GLFWwindow* window) const;

	int key_;
	bool pressed_ = false;
};

namespace std {
	template <>
	struct hash<Key> {
		std::size_t operator()(const Key& key) const {
			return std::hash<int>()(key.GetKey());
		}
	};
}

#endif // SIMULATION_CLASSES_KEY_H_