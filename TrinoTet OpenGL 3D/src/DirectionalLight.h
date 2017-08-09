#ifndef STRIKE_DIRECTIONALLIGHT_H
#define STRIKE_DIRECTIONALLIGHT_H
#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		: Light(ambient, diffuse, specular)
	{
		RenderSystem::Instance().AddDirLight(this);
	}

	~DirectionalLight()
	{
		RenderSystem::Instance().RemoveDirLight(this);
	}
};

#endif
