#ifndef SIMULATION_CLASSES_OBJECT_HANDLER_H_
#define SIMULATION_CLASSES_OBJECT_HANDLER_H_

#include "object.h"
#include <list>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class ObjectHandler {
public:
    void MainCycle(std::list<std::shared_ptr<Object>>& object_list, double delta_time);

private:
    bool CheckCollision(Object* first, Object* second);
    void HandleCollision(Object* first, Object* second, double delta_time);
    bool SATCollision(const std::vector<std::pair<float, float>>& vertices1, const std::vector<std::pair<float, float>>& vertices2);
};

#endif // SIMULATION_CLASSES_OBJECT_HANDLER_H_
