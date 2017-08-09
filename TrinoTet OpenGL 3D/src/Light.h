#ifndef STRIKE_LIGHT_H
#define STRIKE_LIGHT_H
#pragma once

#include <glm/glm.hpp>

#include "Component.h"
#include "RenderSystem.h"

class Light : public Component
{

private:
	// All lights properties
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;


public:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: ambient(ambient), diffuse(diffuse), specular(specular)
	{

	}

	virtual ~Light()
	{

	}

	inline glm::vec3 Ambient() { return ambient; }
	inline glm::vec3 Diffuse() { return diffuse; }
	inline glm::vec3 Specular() { return specular; }
};

#endif
