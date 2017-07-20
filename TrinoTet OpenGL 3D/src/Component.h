#ifndef _SRC_COMPONENT_H
#define _SRC_COMPONENT_H_
#pragma once

#include <iostream>

#include <GL/glew.h>

class Component
{
public:
	virtual ~Component();

	virtual void Update(GLfloat deltaTime) {};
};

#endif