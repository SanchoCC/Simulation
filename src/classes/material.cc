#include "material.h"

Material::Material() {
	density_ = 2.0f;
	restitution_ = 0.5f;
	static_friction_ = 0.5f;
	dynamic_friction_ = 0.25f;
	color_.SetRandomColor();
}

void Material::SetMaterial(MaterialType material_type) {
	switch (material_type) {
	case MaterialType::kDefault:
		density_ = 2.0f;
		restitution_ = 0.5f;
		static_friction_ = 0.5f;
		dynamic_friction_ = 0.25f;
		color_.SetRandomColor();
		break;
	case MaterialType::kRock:
		density_ = 2.4f;
		restitution_ = 0.2f;
		static_friction_ = 0.9f;
		dynamic_friction_ = 0.45f;
		color_.SetColor(128.f / 255.0f, 128.f / 255.0f, 128.f / 255.0f);
		break;
	case MaterialType::kWood:
		density_ = 0.6f;
		restitution_ = 0.4f;
		static_friction_ = 0.4f;
		dynamic_friction_ = 0.2;
		color_.SetColor(121.f / 255.0f, 85.f / 255.0f, 61.f / 255.0f);
		break;
	case MaterialType::kMetal:
		density_ = 7.8f;
		restitution_ = 0.75f;
		static_friction_ = 0.74f;
		dynamic_friction_ = 0.37f;
		color_.SetColor(192.f / 255.0f, 192.f / 255.0f, 192.f / 255.0f);
		break;
	case MaterialType::kIce:
		density_ = 0.9f;
		restitution_ = 0.05f;
		static_friction_ = 0.05f;
		dynamic_friction_ = 0.025f;
		color_.SetColor(173.f / 255.0f, 216.f / 255.0f, 230.f / 255.0f);
		break;
	case MaterialType::kRubber:
		density_ = 1.5f;
		restitution_ = 0.85f;
		static_friction_ = 1.5f;
		dynamic_friction_ = 0.75f;
		color_.SetColor(80.f / 255.0f, 80.f / 255.0f, 80.f / 255.0f);
		break;
	default:
		density_ = 2.0f;
		restitution_ = 0.5f;
		static_friction_ = 0.45f;
		dynamic_friction_ = 0.3f;
		color_.SetRandomColor();
		break;
	}
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
