#include "material.h"

#include "glm/vec3.hpp"

Material::Material() {
	density_ = 2.0f;
	restitution_ = 0.5f;
	static_friction_ = 0.5f;
	dynamic_friction_ = 0.25f;
	color_.SetRandomColor();
}

Material::Material(MaterialType material_type) {
	SetMaterial(material_type);
}

void Material::SetMaterial(MaterialType material_type) {
	glm::vec3 color;
	switch (material_type) {
	case MaterialType::kDefault:
		density_ = 2.0f;
		restitution_ = 0.5f;
		static_friction_ = 0.5f;
		dynamic_friction_ = 0.25f;
		color_.SetRandomColor();
		return;
	case MaterialType::kRock:
		density_ = 2.4f;
		restitution_ = 0.2f;
		static_friction_ = 0.9f;
		dynamic_friction_ = 0.45f;
		color = glm::vec3(128.f, 128.f, 128.f);		
		break;
	case MaterialType::kWood:
		density_ = 0.6f;
		restitution_ = 0.4f;
		static_friction_ = 0.4f;
		dynamic_friction_ = 0.2f;
		color = glm::vec3(121.f, 85.f, 61.f);
		break;
	case MaterialType::kMetal:
		density_ = 7.8f;
		restitution_ = 0.75f;
		static_friction_ = 0.74f;
		dynamic_friction_ = 0.37f;
		color = glm::vec3(192.f, 192.f, 192.f);
		break;
	case MaterialType::kIce:
		density_ = 0.9f;
		restitution_ = 0.05f;
		static_friction_ = 0.05f;
		dynamic_friction_ = 0.025f;
		color = glm::vec3(173.f, 216.f, 230.f);
		break;
	case MaterialType::kRubber:
		density_ = 1.5f;
		restitution_ = 0.85f;
		static_friction_ = 1.5f;
		dynamic_friction_ = 0.75f;
		color = glm::vec3(80.f, 80.f, 80.f);
		break;
	default:
		density_ = 2.0f;
		restitution_ = 0.5f;
		static_friction_ = 0.45f;
		dynamic_friction_ = 0.3f;
		color_.SetRandomColor();
		return;
	}
	color /= 255.f;
	color_.SetColor(color);
}

Color Material::GetColor() const {
	return color_;
}

float Material::GetDensity() const {
	return density_;
}

float Material::GetRestitution() const {
	return restitution_;
}

float Material::GetStaticFriction() const {
	return static_friction_;
}

float Material::GetDynamicFriction() const {
	return dynamic_friction_;
}
