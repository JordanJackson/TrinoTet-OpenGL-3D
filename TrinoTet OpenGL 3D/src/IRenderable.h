#ifndef _SRC_IRENDERABLE_H_
#define _SRC_IRENDERABLE_H_
#pragma once

#include <GL/glew.h>

class IRenderable
{
public:
	virtual void Render(GLfloat deltaTime) {};
};

#endif