#ifndef SIMULATION_CLASSES_OBJECT_HANDLER_H_
#define SIMULATION_CLASSES_OBJECT_HANDLER_H_

#include <list>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>

#include "object.h"
#include "settings.h"

struct CollisionResult {
	float penetration;
	glm::vec2 normal;
	std::vector<glm::vec2> contacts;
};

class ObjectHandler {
public:
	static ObjectHandler& Get();
	ObjectHandler(ObjectHandler const&) = delete;
	void operator=(ObjectHandler const&) = delete;
	~ObjectHandler();

	void MainCycle(float delta_time);

	void AddInObjects(Object* object);
	void AddInCreatedObjects(Object* object);

	void DeleteObject(Object* object);

	std::list<Object*> GetObjects();

	CollisionResult CheckCollision(const Object* object1, const Object* object2) const;
private:
	ObjectHandler();

	void Accelerate(Object* object, glm::vec2 acceleration, float delta_time);
	void Move(Object* object, float delta_time);
	void Rotate(Object* object, float delta_time);
	void ApplyImpulse(Object* object, glm::vec2 impulse, glm::vec2 contact_vector);
	void SeparateObjects(Object* object1, Object* object2, CollisionResult collision_result);	
	CollisionResult SATCollision(const Object* object1, const Object* object2) const;
	CollisionResult CircleCircle(const Object* object1, const Object* object2) const;
	CollisionResult CircleRectangle(const Object* object1, const Object* object2) const;
	void HandleCollision(Object* object1, Object* object2, CollisionResult collision_result);

	float gravity_ = Settings::Get().world_parameters_.gravity;
	std::list<Object*> objects_;
	std::list<Object*> created_objects_;
};

#endif // SIMULATION_CLASSES_OBJECT_HANDLER_H_
