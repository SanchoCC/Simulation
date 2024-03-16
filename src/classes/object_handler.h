#ifndef SIMULATION_CLASSES_OBJECT_HANDLER_H_
#define SIMULATION_CLASSES_OBJECT_HANDLER_H_

#include "object.h"
#include <list>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class ObjectHandler {
public:
    void MainCycle(std::list<std::shared_ptr<Object>>& object_list, float delta_time);

private:
    void Accelerate(Object* object, float acceleration_x, float acceleration_y, float delta_time );
    void Move(Object*, float delta_time);
    bool CheckCollision(Object* first, Object* second) const;
    float SATCollision(Object* first, Object* second) const;
    void HandleCollision(Object* first, Object* second, float delta_time);   
    void SeparateObjects(Object* first, Object* second, float penetration_depth);

    const float kGravity = -0.98f;
};

#endif // SIMULATION_CLASSES_OBJECT_HANDLER_H_
