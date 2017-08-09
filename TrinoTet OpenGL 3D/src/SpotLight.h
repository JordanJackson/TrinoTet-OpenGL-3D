#ifndef STRIKE_SPOTLIGHT_H
#define STRIKE_SPOTLIGHT_H
#pragma once

#include "Light.h"

class SpotLight : public Light
{
private:
	// Spot light properties
	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;
	GLfloat cutOff;
	GLfloat outerCutOff;

public:
	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		GLfloat constant, GLfloat linear, GLfloat quadratic, GLfloat cutOff, GLfloat outerCutOff)
		: Light(ambient, diffuse, specular),
		constant(constant), linear(linear), quadratic(quadratic),
		cutOff(cutOff), outerCutOff(outerCutOff)
	{
		RenderSystem::Instance().AddSpotLight(this);
	}

	~SpotLight()
	{
		RenderSystem::Instance().RemoveSpotLight(this);
	}

	inline GLfloat Constant() { return constant; }
	inline GLfloat Linear() { return linear; }
	inline GLfloat Quadratic() { return quadratic; }

	inline GLfloat CutOff() { return cutOff; }
	inline GLfloat OuterCutOff() { return outerCutOff; }
};

#endif
