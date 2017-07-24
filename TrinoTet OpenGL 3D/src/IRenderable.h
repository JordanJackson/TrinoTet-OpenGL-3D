#ifndef _SRC_IRENDERABLE_H_
#define _SRC_IRENDERABLE_H_
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderSystem.h"

class IRenderable
{
public:
	IRenderable()
	{
		RenderSystem::Instance().AddRenderable(this);
	}

	virtual ~IRenderable()
	{
		RenderSystem::Instance().RemoveRenderable(this);
	}

	virtual void Render(glm::mat4 view, glm::mat4 projection) = 0;
};

#endif