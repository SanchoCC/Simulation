#include "Object.h"

std::list<std::shared_ptr<Object>> Object::objects_list_;

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);

rgb hsvToRgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i) {
        case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
        case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
        case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

        case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
        case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
        case 5:
        default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

Object::Object(bool collision, bool statical, float position_x, float position_y) { 
    this->collision_ = collision;
    this->statical_ = statical;
    this->position_x_ = position_x;
    this->position_y_ = position_y;     
}
Object::~Object() {   
}
void Object::ObjectsMain(double deltaTime) {
    for (auto it = objects_list_.begin(); it != objects_list_.end(); ++it) {        
        (*it)->GravityAcceleration(deltaTime);
        (*it)->Move(deltaTime);
        for (auto innerit = objects_list_.begin(); innerit != objects_list_.end(); ++innerit) {
            if (innerit == it) {
                continue;
            } else if ((*it)->CheckCollision(*innerit)) {
                (*it)->CollisionEffect(*innerit, deltaTime);
            }
        }        
        (*it)->Render();
    }
}
void Object::GravityAcceleration(double deltaTime) {
    velocity_y_ -= 9.8f;
}
void Object::Move(double deltaTime) {
    if (!statical_) {        
        position_x_ += (velocity_x_*0.001f) * deltaTime;
        position_y_ += (velocity_y_*0.001f) * deltaTime;
        UpdateAngles();
    } else {
        velocity_x_ = 0;
        velocity_y_ = -9.8;
    }    
}
Object::Color::Color() {
    SetRandomColor();
}
Object::Color::Color(float red, float green, float blue) {
    SetColor(red, green, blue);
}
void Object::Color::SetRandomColor() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> hue_dist(0.0f, 360.0f); 
    std::uniform_real_distribution<float> sat_dist(0.3f, 0.5f);
    std::uniform_real_distribution<float> val_dist(0.9f, 1);

    float hue = hue_dist(rng);
    float saturation = sat_dist(rng);
    float value = val_dist(rng);

    hsv input;
    rgb output;

    input.h = hue;
    input.s = saturation;
    input.v = value;
    
    output = hsvToRgb(input);

    this->red_ = output.r;
    this->green_ = output.g;
    this->blue_ = output.b;
}

void Object::Color::SetColor(float red, float green, float blue) {
    this->red_ = red;
    this->green_ = green;
    this->blue_ = blue;
}
bool Object::GetIsRectangle() const {
    return this->is_rectangle_;
}
float Object::GetRotationAngle() const {
    return this->rotation_angle_;
}
float Object::GetMaxAngleX() const {
    auto max = *std::max_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });   
    return max.first;
}
float Object::GetMinAngleX() const {
    auto min = *std::min_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });   
    return min.first;
}
float Object::GetMaxAngleY() const {
    auto max = *std::max_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return max.second;
}
float Object::GetMinAngleY() const {
    auto min = *std::min_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return min.second;
}
float Object::GetMass() const {
    return mass_;
}
float Object::GetVelocityX() const {
    return velocity_x_;
}
float Object::GetVelocityY() const {
    return velocity_y_;
}
void Object::SetVelocityX(float velocity_x) {
    this->velocity_x_ = velocity_x;
}
void Object::SetVelocityY(float velocity_y) {
    this->velocity_y_ = velocity_y;
}
float Object::GetTension() const {
    return this->tension_;
}
void Object::SetTension(float tension) {
    this->tension_ = tension;
}
