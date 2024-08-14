#include "inputs.h"

#include <random>

#include "object_shapes.h"
#include "settings.h"
#include "glfw_callback.h"

Inputs& Inputs::Get() {
	static Inputs instance;

	return instance;
}

Inputs::Inputs() {
	actions_.push_back(std::make_pair(&spawn_circle_key_, std::bind(&Inputs::SpawnCircle, this, std::placeholders::_1, std::placeholders::_2)));
	actions_.push_back(std::make_pair(&spawn_chaotic_circle_key, std::bind(&Inputs::SpawnChaoticCircle, this, std::placeholders::_1, std::placeholders::_2)));
	actions_.push_back(std::make_pair(&pause_key_, std::bind(&Inputs::Pause, this, std::placeholders::_1, std::placeholders::_2)));
	actions_.push_back(std::make_pair(&increase_simulation_speed_key_, std::bind(&Inputs::IncreaseSimulationSpeed, this, std::placeholders::_1, std::placeholders::_2)));
	actions_.push_back(std::make_pair(&decrease_simulation_speed_key_, std::bind(&Inputs::DecreaseSimulationSpeed, this, std::placeholders::_1, std::placeholders::_2)));
}

void Inputs::CheckInputs(GLFWwindow* window, float& delta_time) {
		for (auto it : actions_) {
			it.first->Action(it.second, window, delta_time);
		}
	}

void Inputs::SpawnCircle(GLFWwindow* window, float& delta_time) {
	glm::vec2 position = GetCursorWorldPosition(window);
	Circle* circle = new Circle(position.x, position.y, 0.3f, MaterialType::kDefault);
}

void Inputs::SpawnChaoticCircle(GLFWwindow* window, float& delta_time) {
	glm::vec2 position = GetCursorWorldPosition(window);

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> size_dist(0.05f, 0.4f);
	float radius = size_dist(rng);

	std::uniform_int_distribution<int> material_dist(0, 5);
	MaterialType material = static_cast<MaterialType>((material_dist(rng)));


	std::uniform_real_distribution<float> vel_x_dist(-2.0f, 2.0f);
	float velocity_x = vel_x_dist(rng);

	std::uniform_real_distribution<float> vel_y_dist(-2.0f, 2.0f);
	float velocity_y = vel_y_dist(rng);

	std::uniform_real_distribution<float> angular_velocity_dist(-1.f, 1.f);
	float angular_velocity = angular_velocity_dist(rng);
	
	
	Circle* circle = new Circle(position.x, position.y, radius, material);
	circle->SetVelocity(glm::vec2(velocity_x, velocity_y));
	circle->SetAngularVelocity(angular_velocity);
}

void Inputs::Pause(GLFWwindow* window, float& delta_time) {
	float& simulation_speed = Settings::Get().world_parameters_.simulation_speed;
	if (simulation_speed < 0.1f && simulation_speed > -0.1f) {
		simulation_speed = last_simulaion_speed_;
	} else {
		last_simulaion_speed_ = simulation_speed;
		Settings::Get().world_parameters_.simulation_speed = 0.f;
	}	
}

void Inputs::IncreaseSimulationSpeed(GLFWwindow* window, float& delta_time) {
	float& simulation_speed = Settings::Get().world_parameters_.simulation_speed;
	if (simulation_speed < 1.9f) {
		simulation_speed *= 2.f;
	}
}

void Inputs::DecreaseSimulationSpeed(GLFWwindow* window, float& delta_time) {	
	float& simulation_speed = Settings::Get().world_parameters_.simulation_speed;
	if (simulation_speed > 0.26f)
	simulation_speed *= 0.5f;
}