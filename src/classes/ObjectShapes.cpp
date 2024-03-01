#include "ObjectShapes.h"

Circle::Circle(bool Collision, bool Static, float PositionX, float PositionY, float Radius) :Object(Collision, Static, PositionX, PositionY) {
    this->Radius = Radius;
    ObjectsList.push_back(std::make_shared<Circle>(*this));
}

void Circle::Render() {
    Angles.clear();
    int Sides = kCircleSides * Radius;
    glColor3f(Color.Red, Color.Green, Color.Blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < Sides; ++i) {
        float theta = 2.0f * M_PI * i / Sides - (M_PI / 4 + (RotationAngle / 180 * M_PI));
        Angles.push_back(std::make_pair(Radius * cosf(theta) + PositionX, Radius * sinf(theta) + PositionY));
        glVertex2f(Angles[i].first, Angles[i].second);
    }
    glEnd();
}
Rectangle::Rectangle(bool Collision, bool Static, float PositionX, float PositionY, float Height, float Width) :Object(Collision, Static, PositionX, PositionY) {
    this->IsRectangle = true;
    this->Height = Height;
    this->Width = Width;
    this->Render();
    ObjectsList.push_back(std::make_shared<Rectangle>(*this));
}
void Rectangle::Render() {
    Angles.clear();
    std::vector<std::pair<float, float>> OriginalAngles = {
        std::make_pair(-Width / 2, Height / 2),
        std::make_pair(Width / 2, Height / 2),
        std::make_pair(Width / 2, -Height / 2),
        std::make_pair(-Width / 2, -Height / 2)
    };
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-RotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
    for (const auto& it : OriginalAngles) {
        glm::vec4 vertex = glm::vec4(it.first, it.second, 0.0f, 1.0f);
        vertex = model * vertex;
        Angles.push_back(std::make_pair(vertex.x+PositionX, vertex.y+PositionY));
    }
    glColor3f(Color.Red, Color.Green, Color.Blue);
    glBegin(GL_POLYGON);
    for (const auto& it : Angles) {
        glVertex2f(it.first, it.second);
    }
    glEnd();
}
bool Rectangle::CheckCollision(const std::shared_ptr <Object>& Other) {
    if (Other->GetIsRectangle()) {
        auto MinThis = *std::min_element(Angles.cbegin(), Angles.cend(), [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
            });
        auto MinOther = *std::min_element(Other->Angles.cbegin(), Other->Angles.cend(), [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
            });
        auto MaxThis = *std::max_element(Angles.cbegin(), Angles.cend(), [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
            });
        auto MaxOther = *std::max_element(Other->Angles.cbegin(), Other->Angles.cend(), [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
            });        
        if (MinThis.first >= MinOther.first && MinThis.first <= MaxOther.first || MaxThis.first <= MaxOther.first && MaxThis.first >= MinOther.first) {
            MinThis = *std::min_element(Angles.cbegin(), Angles.cend(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
                });
            MinOther = *std::min_element(Other->Angles.cbegin(), Other->Angles.cend(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
                });
            MaxThis = *std::max_element(Angles.cbegin(), Angles.cend(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
                });
            MaxOther = *std::max_element(Other->Angles.cbegin(), Other->Angles.cend(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
                });           
            if (MinThis.second >= MinOther.second && MinThis.second <= MaxOther.second || MaxThis.second <= MaxOther.second && MaxThis.second >= MinOther.second) {
                return true;
            } 
        } 
    } 
    return false;
}