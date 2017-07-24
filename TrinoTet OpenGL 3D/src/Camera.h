#ifndef _SRC_CAMERA_H_
#define _SRC_CAMERA_H_
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Component.h"
#include "Transform.h"

class Camera : public Component
{
protected:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void Initialize();

public:
	Camera(const glm::mat4& projectionMatrix);

	inline const glm::mat4& GetViewMatrix() const { return viewMatrix; }
	inline const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }

private:
	void ComputeViewMatrix();

	friend class RenderSystem;
};

#endif
