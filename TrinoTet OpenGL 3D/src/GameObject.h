#ifndef _SRC_GAMEOBJECT_H_
#define _SRC_GAMEOBJECT_H_
#pragma once

#include <map>

#include <GL/glew.h>

#include "Component.h"
#include "Transform.h"

class GameObject
{
private:
	Transform* transform;
	std::multimap<GLuint, Component*> components;

public:
	GameObject();
	~GameObject();

	void AddComponent(Component* component);
	void RemoveComponent(GLuint typeHash);

	Component* GetComponentByType(GLuint typeHash);

	virtual void Update(GLfloat deltaTime);
};

#endif