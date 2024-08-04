#ifndef SIMULATION_CLASSES_MATERIAL_H_
#define SIMULATION_CLASSES_MATERIAL_H_

#include "color.h"

enum class MaterialType {
    kDefault,
    kRock,
    kWood,
    kMetal,
    kIce,
    kRubber
};

class Material {
public:
    Material();

    void SetMaterial(MaterialType material_type);
    Color GetColor() const;
    float GetDensity() const;
    float GetRestitution() const;
    float GetStaticFriction() const;
    float GetDynamicFriction() const;

private:
    float density_;
    float restitution_;
    float static_friction_;
    float dynamic_friction_;
    Color color_;
};

#endif SIMULATION_CLASSES_MATERIAL_H_