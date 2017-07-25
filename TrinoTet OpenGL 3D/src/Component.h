#ifndef _SRC_COMPONENT_H
#define _SRC_COMPONENT_H_
#pragma once

#include <iostream>

#include <GL/glew.h>

class GameObject;
class Transform;

class Component
{
protected:
	GameObject* gameObject;
	Transform* transform;


public:
	virtual ~Component();

	virtual void Update(GLfloat deltaTime) {};

	inline GameObject& GameObject() { return *gameObject; }
	inline Transform& Transform() { return *transform; }

	friend class GameObject;
};

#endif