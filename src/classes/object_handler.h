#ifndef SIMULATION_CLASSES_OBJECT_HANDLER_H_
#define SIMULATION_CLASSES_OBJECT_HANDLER_H_

#include <list>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "object.h"

struct CollisionResult {
    float penetration;
    glm::vec2 normal;
    std::vector <glm::vec2> contacts;
};

class ObjectHandler {
public:
    void MainCycle(std::list<std::shared_ptr<Object>>& object_list, float delta_time);
    

private:
    void Accelerate(Object* object, glm::vec2 acceleration, float delta_time );
    void Move(Object* object, float delta_time);
    void Rotate(Object* object, float delta_time);
    void ApplyImpulse(Object* object, glm::vec2 impulse, glm::vec2 contact_vector);
    void SeparateObjects(Object* object1, Object* object2, CollisionResult collision_result);
    CollisionResult CheckCollision(Object* object1, Object* object2) const;
    CollisionResult SATCollision(Object* object1, Object* object2) const;
    CollisionResult CircleCircle(Object* object1, Object* object2) const;
    CollisionResult CircleRectangle(Object* object1, Object* object2) const;
    void HandleCollision(Object* object1, Object* object2, CollisionResult collision_result, float delta_time);

    /*glm::vec2 FindSupportVertex(Object* object, glm::vec2 direction);*/
    
    const float kGravity = -0.98f;
};

#endif // SIMULATION_CLASSES_OBJECT_HANDLER_H_
