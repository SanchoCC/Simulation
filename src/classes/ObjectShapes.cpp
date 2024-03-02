#include "ObjectShapes.h"

Circle::Circle(bool collision, bool statical, float position_x, float position_y, float radius) :Object(collision, statical, position_x, position_y) {
    this->radius_ = radius;
    objects_list_.push_back(std::make_shared<Circle>(*this));
}

void Circle::Render() {
    angles_.clear();
    int sides = kCircleSides * radius_;
    glColor3f(color_.red_, color_.green_, color_.blue_);
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; ++i) {
        float theta = 2.0f * M_PI * i / sides - (M_PI / 4 + (rotation_angle_ / 180 * M_PI));
        angles_.push_back(std::make_pair(radius_ * cosf(theta) + position_x_, radius_ * sinf(theta) + position_y_));
        glVertex2f(angles_[i].first, angles_[i].second);
    }
    glEnd();
}
Rectangle::Rectangle(bool collision, bool statical, float position_x, float position_y, float width, float height) :Object(collision, statical, position_x, position_y) {
    this->is_rectangle_ = true;
    this->width_ = width;
    this->height_ = height;   
    this->Render();
    objects_list_.push_back(std::make_shared<Rectangle>(*this));
}
void Rectangle::Render() {
    this->mass_ = (width_ * height_) * density_;
    angles_.clear();
    std::vector<std::pair<float, float>> original_angles_ = {
        std::make_pair(-width_ / 2, height_ / 2),
        std::make_pair(width_ / 2, height_ / 2),
        std::make_pair(width_ / 2, -height_ / 2),
        std::make_pair(-width_ / 2, -height_ / 2)
    };
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-rotation_angle_), glm::vec3(0.0f, 0.0f, 1.0f));
    for (const auto& it : original_angles_) {
        glm::vec4 vertex = glm::vec4(it.first, it.second, 0.0f, 1.0f);
        vertex = model * vertex;
        angles_.push_back(std::make_pair(vertex.x+position_x_, vertex.y+position_y_));
    }
    glColor3f(color_.red_, color_.green_, color_.blue_);
    glBegin(GL_POLYGON);
    for (const auto& it : angles_) {
        glVertex2f(it.first, it.second);
    }
    glEnd();
}
bool Rectangle::CheckCollision(const std::shared_ptr <Object>& other) {
    if (other->GetIsRectangle()) {
        float min_this_x = this->GetMinAngleX();
        float min_other_x = other->GetMinAngleX();
        float max_this_x = this->GetMaxAngleX();
        float max_other_x = other->GetMaxAngleX();
        if (min_this_x >= min_other_x && min_this_x <= max_other_x || max_this_x <= max_other_x && max_this_x >= min_other_x) {        
            float min_this_y = this->GetMinAngleY();
            float min_other_y = other->GetMinAngleY();
            float max_this_y = this->GetMaxAngleY();
            float max_other_y = other->GetMaxAngleY();
            if (min_this_y >= min_other_y && min_this_y <= max_other_y || max_this_y <= max_other_y && max_this_y >= min_other_y) {
                return true;
            } 
        } 
    } 
    return false;
}
void Rectangle::CollisionEffect(std::shared_ptr <Object>& other, double deltaTime) {
    this->Move(-deltaTime);
    float this_mass = this->mass_;
    float other_mass = other->GetMass();
    float this_velocity_x = velocity_x_;
    float other_velocity_x = other->GetVelocityX();
    float this_velocity_y = velocity_y_;
    float other_velocity_y = other->GetVelocityY();    
    this->SetVelocityX(-((this_mass - other_mass) * this_velocity_x + (2*other_mass*other_velocity_x))/(this_mass * other_mass));
    other->SetVelocityX(((other_mass - this_mass) * other_velocity_x + (2 * this_mass * this_velocity_x)) / (this_mass * other_mass));
    this->SetVelocityY((((this_mass - other_mass) * this_velocity_y + (2 * other_mass * other_velocity_y)) / (this_mass * other_mass)));
    other->SetVelocityY((((other_mass - this_mass) * other_velocity_y + (2 * this_mass * this_velocity_y)) / (this_mass * other_mass)));
}