#ifndef _SRC_TRANSFORM_H_
#define _SRC_TRANSFORM_H_
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Component.h"

class Transform : public Component
{
private:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

public:
	Transform();
	~Transform();

	void Update(GLfloat deltaTime) override;
};

#endif