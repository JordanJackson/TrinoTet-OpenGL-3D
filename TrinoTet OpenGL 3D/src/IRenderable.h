#ifndef _SRC_IRENDERABLE_H_
#define _SRC_IRENDERABLE_H_
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Material.h"
#include "Component.h"
#include "RenderSystem.h"

class IRenderable : public Component
{
protected:
	Material* material;

public:
	IRenderable() : material(nullptr)
	{
		RenderSystem::Instance().AddRenderable(this);
	}

	IRenderable(Material& material) : material(&material)
	{
		RenderSystem::Instance().AddRenderable(this);
	}

	virtual ~IRenderable()
	{
		RenderSystem::Instance().RemoveRenderable(this);
	}

	virtual void Render(glm::mat4 view, glm::mat4 projection) = 0;

	inline Material& GetMaterial() { return *material; }
};

#endif