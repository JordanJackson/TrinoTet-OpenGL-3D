#ifndef STRIKE_POINTLIGHT_H
#define STRIKE_POINTLIGHT_H
#pragma once

#include "Light.h"

class PointLight : public Light
{
private:
	// Point light properties
	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;
public:
	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat constant, GLfloat linear, GLfloat quadratic)
		: Light(ambient, diffuse, specular), constant(constant), linear(linear), quadratic(quadratic)
	{
		RenderSystem::Instance().AddPointLight(this);
	}

	~PointLight()
	{
		RenderSystem::Instance().RemovePointLight(this);
	}

	inline GLfloat Constant() { return constant; }
	inline GLfloat Linear() { return linear; }
	inline GLfloat Quadratic() { return quadratic; }
};

#endif
