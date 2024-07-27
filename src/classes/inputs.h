#ifndef SIMULATION_CLASSES_INPUTS_H_
#define SIMULATION_CLASSES_INPUTS_H_

#include <vector>
#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "key.h"

class Inputs {
public:
	static Inputs& GetInstance();
	Inputs(Inputs const&) = delete;
	void operator=(Inputs const&) = delete;

	void CheckInputs(GLFWwindow* window, float& delta_time);

private:
	Inputs();

	void SpawnCircle(GLFWwindow* window, float& delta_time);
	void Pause(GLFWwindow* window, float& delta_time);
	void IncreaseSimulationSpeed(GLFWwindow* window, float& delta_time);
	void DecreaseSimulationSpeed(GLFWwindow* window, float& delta_time);

	std::vector <std::pair<Key*, std::function<void(GLFWwindow*, float&)>>> actions_;

	Key spawn_circle_key_ = Key(GLFW_KEY_Q);
	Key pause_key_ = Key(GLFW_KEY_SPACE);
	Key increase_simulation_speed_key_ = Key(GLFW_KEY_RIGHT);
	Key decrease_simulation_speed_key_ = Key(GLFW_KEY_LEFT);

	float last_simulaion_speed_ = 1.f;

};

#endif //SIMULATION_CLASSES_INPUTS_H_
