#ifndef _SRC_IRENDERABLE_H_
#define _SRC_IRENDERABLE_H_
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IRenderable
{
public:
	virtual void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, GLfloat deltaTime) {};
};

#endif