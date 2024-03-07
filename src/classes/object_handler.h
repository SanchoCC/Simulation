#pragma once
#ifndef SIMULATION_CLASSES_OBJECT_HANDLER_H_
#define SIMULATION_CLASSES_OBJECT_HANDLER_H_
#include "object.h"

class ObjectHandler {
 public:
	void MainCycle(std::list <std::shared_ptr<Object>>& object_list, double delta_time);

 private:
	bool CheckCollision(Object* first, Object* second);
	void HandleCollision(Object* first, Object* second, float delta_time);
	float CalculateNewVelocity(float mass_self, float velocity_self, float mass_other, float velocity_other, float tension_self, float tension_other);
};

#endif //SIMULATION_CLASSES_OBJECT_HANDLER_H_
