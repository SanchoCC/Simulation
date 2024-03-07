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
        std::pair <float, float> max_second = second->GetMinVertices();
        bool collision_x = max_first.first >= min_second.first && min_first.first <= max_second.first;
        bool collision_y = max_first.second >= min_second.second && min_first.second <= max_second.second;
        return collision_x && collision_y;
    } else if (first->GetType() == ShapeType::kCircle && second->GetType() == ShapeType::kCircle) {
        return true;
    }   
}
float ObjectHandler::CalculateNewVelocity(float mass_self, float velocity_self, float mass_other, float velocity_other, float tension_self, float tension_other) {
    return (((mass_self - mass_other) * velocity_self + 2 * mass_other * velocity_other) / (mass_self + mass_other)) * (0.5f * (tension_self + tension_other)) * -1;
}

void ObjectHandler::HandleCollision(Object* first, Object* second, float delta_time) {
    first->Move(-delta_time);
    second->Move(-delta_time);
    float first_mass = first->GetMass();
    float first_velocity_x = first->GetVelocityX();
    float first_velocity_y = first->GetVelocityY();
    float first_tension = first->GetTension();
    float second_mass = second->GetMass();
    float second_velocity_x = second->GetVelocityX();
    float second_velocity_y = second->GetVelocityY();
    float second_tension = second->GetTension();
    float new_velocity_x_first = CalculateNewVelocity(first_mass, first_velocity_x, second_mass, second_velocity_x, first_tension, second_tension);
    float new_velocity_y_first = CalculateNewVelocity(first_mass, first_velocity_y, second_mass, second_velocity_y, first_tension, second_tension);
    float new_velocity_x_second = CalculateNewVelocity(second_mass, second_velocity_x, first_mass, first_velocity_x, second_tension, first_tension);
    float new_velocity_y_second = CalculateNewVelocity(second_mass, second_velocity_y, first_mass, first_velocity_y, second_tension, first_tension);
    first->SetVelocityX(new_velocity_x_first);
    first->SetVelocityY(new_velocity_y_first);
    second->SetVelocityX(new_velocity_x_second);
    second->SetVelocityY(new_velocity_y_second);
}