#ifndef SIMULATION_CLASSES_OBJECT_HANDLER_H_
#define SIMULATION_CLASSES_OBJECT_HANDLER_H_

#include <list>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "object.h"
#include "settings.h"

struct CollisionResult {
    float penetration;
    glm::vec2 normal;
    std::vector <glm::vec2> contacts;
};

class ObjectHandler {
public:
    static ObjectHandler& GetInstance();
    ObjectHandler(ObjectHandler const&) = delete;
    void operator=(ObjectHandler const&) = delete;

    void MainCycle(std::list<Object*>& object_list, float delta_time);
private:
    ObjectHandler();
    
    void Accelerate(Object* object, glm::vec2 acceleration, float delta_time);
    void Move(Object* object, float delta_time);
    void Rotate(Object* object, float delta_time);
    void ApplyImpulse(Object* object, glm::vec2 impulse, glm::vec2 contact_vector);
    void SeparateObjects(Object* object1, Object* object2, CollisionResult collision_result);
    CollisionResult CheckCollision(const Object* object1, const Object* object2) const;
    CollisionResult SATCollision(const Object* object1, const Object* object2) const;
    CollisionResult CircleCircle(const Object* object1, const Object* object2) const;
    CollisionResult CircleRectangle(const Object* object1, const Object* object2) const;
    void HandleCollision(Object* object1, Object* object2, CollisionResult collision_result);

    /*glm::vec2 FindSupportVertex(Object* object, glm::vec2 direction);*/
    
    float gravity_ = Settings::GetInstance().world_parameters_.gravity;
};

#endif // SIMULATION_CLASSES_OBJECT_HANDLER_H_
