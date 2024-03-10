#include "object_handler.h"

void ObjectHandler::MainCycle(std::list <std::shared_ptr<Object>>& object_list, double delta_time) {
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
    if (first->GetType() == ShapeType::kRectangle && second->GetType() == ShapeType::kRectangle) {
        std::pair <float, float> min_first = first->GetMinVertices();
        std::pair <float, float> min_second = second->GetMinVertices();
        std::pair <float, float> max_first = first->GetMaxVertices();
        std::pair <float, float> max_second = second->GetMaxVertices();
        bool collision_x = max_first.first >= min_second.first && min_first.first <= max_second.first;
        bool collision_y = max_first.second >= min_second.second && min_first.second <= max_second.second;
        return collision_x && collision_y;
    }
    else if (first->GetType() == ShapeType::kCircle && second->GetType() == ShapeType::kCircle) {
        return (glm::distance(first->GetPositionVec2(), second->GetPositionVec2())) <= first->GetRadius() + second->GetRadius();
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