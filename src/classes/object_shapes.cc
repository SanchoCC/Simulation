#include "object_shapes.h"

Circle::Circle(bool statical, float position_x, float position_y, float radius) : Object(statical, position_x, position_y) {
    this->radius_ = radius;
    this->mass_ = M_PI * radius * radius * density_;
    this->UpdateVertices();
    this->Render();
    shared_this_ = (std::make_shared<Circle>(*this));
    objects_list_.push_back(shared_this_);
}

ShapeType Circle::GetType() const {
    return ShapeType::kCircle;
}

void Circle::Render() {
    glColor3f(color_.red_, color_.green_, color_.blue_);
    glBegin(GL_POLYGON);
    for (const auto& it : vertices_) {
        glVertex2f(it.first, it.second);
    }
    glEnd();
}

void Circle::UpdateVertices() {
    vertices_.clear();
    int sides = kCircleSides * radius_;
    for (int i = 0; i < sides; ++i) {
        float theta = 2.0f * M_PI * i / sides - (M_PI / 4 + (rotation_angle_ / 180 * M_PI));
        vertices_.push_back(std::make_pair(radius_ * cosf(theta) + position_x_, radius_ * sinf(theta) + position_y_));
    }
}

float Circle::GetRadius() {
    return radius_;
}

Rectangle::Rectangle(bool statical, float position_x, float position_y, float width, float height) : Object(statical, position_x, position_y) {
    this->width_ = width;
    this->height_ = height;
    this->mass_ = (width_ * height_) * density_;
    this->UpdateVertices();
    this->Render();
    shared_this_ = (std::make_shared<Rectangle>(*this));
    objects_list_.push_back(shared_this_);
}

ShapeType Rectangle::GetType() const {
    return ShapeType::kRectangle;
}

void Rectangle::Render() {
    glColor3f(color_.red_, color_.green_, color_.blue_);
    glBegin(GL_POLYGON);
    for (const auto& it : vertices_) {
        glVertex2f(it.first, it.second);
    }
    glEnd();
}

void Rectangle::UpdateVertices() {
    vertices_.clear();
    std::vector<std::pair<float, float>> original_vertices_ = {
        std::make_pair(-width_ / 2, height_ / 2),
        std::make_pair(width_ / 2, height_ / 2),
        std::make_pair(width_ / 2, -height_ / 2),
        std::make_pair(-width_ / 2, -height_ / 2)
    };
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-rotation_angle_), glm::vec3(0.0f, 0.0f, 1.0f));
    for (const auto& it : original_vertices_) {
        glm::vec4 vertex = glm::vec4(it.first, it.second, 0.0f, 1.0f);
        vertex = model * vertex;
        vertices_.push_back(std::make_pair(vertex.x + position_x_, vertex.y + position_y_));
    }
}

float Rectangle::GetRadius() {
    return sqrt(width_ * width_ + height_ * height_);
}
