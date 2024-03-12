#include "object_handler.h"

void ObjectHandler::MainCycle(std::list<std::shared_ptr<Object>>& object_list, double delta_time) {
    for (auto it = object_list.begin(); it != object_list.end(); ++it) {
        auto first = it->get();
        first->GravityAcceleration(delta_time);
        first->Move(delta_time);

        for (auto inner_it = std::next(it); inner_it != object_list.end(); ++inner_it) {
            auto second = inner_it->get();
            if (CheckCollision(first, second)) {
                HandleCollision(first, second, delta_time);
            }
        }

        first->Render();
    }
}

bool ObjectHandler::CheckCollision(Object* first, Object* second) {
    if (first->GetType() == ShapeType::kRectangle || second->GetType() == ShapeType::kRectangle) {
        return SATCollision(first->GetVertices(), second->GetVertices());
    } else if (first->GetType() == ShapeType::kCircle && second->GetType() == ShapeType::kCircle) {
            float distance = glm::distance(first->GetPositionVec2(), second->GetPositionVec2());
            float sum_radius = first->GetRadius() + second->GetRadius();
            return distance <= sum_radius;
        }   
    return false;
}

void ObjectHandler::HandleCollision(Object* first, Object* second, double delta_time) {
    first->Move(-delta_time);
    second->Move(-delta_time);

    float first_mass = first->GetMass();
    float second_mass = second->GetMass();
    float first_velocity_x = first->GetVelocityX();
    float second_velocity_x = second->GetVelocityX();
    float first_velocity_y = first->GetVelocityY();
    float second_velocity_y = second->GetVelocityY();

    first->SetVelocityX((((first_mass - second_mass) * first_velocity_x + 2 * second_mass * second_velocity_x) / (first_mass + second_mass)) * (0.5f * (first->GetTension() + second->GetTension())));
    first->SetVelocityY((((first_mass - second_mass) * first_velocity_y + 2 * second_mass * second_velocity_y) / (first_mass + second_mass)) * (0.5f * (first->GetTension() + second->GetTension())));
    second->SetVelocityX((((second_mass - first_mass) * second_velocity_x + 2 * first_mass * first_velocity_x) / (first_mass + second_mass)) * (0.5f * (first->GetTension() + second->GetTension())));
    second->SetVelocityY((((second_mass - first_mass) * second_velocity_y + 2 * first_mass * first_velocity_y) / (first_mass + second_mass)) * (0.5f * (first->GetTension() + second->GetTension())));   
}

bool ObjectHandler::SATCollision(const std::vector<std::pair<float, float>>& vertices1, const std::vector<std::pair<float, float>>& vertices2) {
    auto calculateAxes = [](const std::vector<std::pair<float, float>>& vertices) {
        std::vector<glm::vec2> axes;
        for (size_t i = 0; i < vertices.size(); ++i) {
            size_t j = (i + 1) % vertices.size();
            glm::vec2 edge = glm::vec2(vertices[j].first - vertices[i].first, vertices[j].second - vertices[i].second);
            axes.push_back(glm::normalize(glm::vec2(-edge.y, edge.x)));
        }
        return axes;
        };

    std::vector<glm::vec2> axes1 = calculateAxes(vertices1);
    std::vector<glm::vec2> axes2 = calculateAxes(vertices2);

    for (const auto& axis : axes1) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        for (const auto& vertex : vertices1) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();
        for (const auto& vertex : vertices2) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    for (const auto& axis : axes2) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        for (const auto& vertex : vertices1) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();
        for (const auto& vertex : vertices2) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        if (max1 < min2 || max2 < min1) {
            return false;
        }
    }

    return true;
}