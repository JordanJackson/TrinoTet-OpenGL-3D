#ifndef _SRC_GAMEOBJECT_H_
#define _SRC_GAMEOBJECT_H_
#pragma once

#include <map>

#include <GL/glew.h>

#include "Component.h"
#include "Mesh.h"
#include "IRenderable.h"
#include "Transform.h"

class GameObject
{
private:
	Transform* transform;
	std::multimap<GLuint, Component*> components;
	std::multimap<GLuint, IRenderable*> renderables;

public:
	GameObject();
	~GameObject();

	void AddComponent(Component* component);
	void RemoveComponent(GLuint typeHash);

	Component* GetComponentByType(GLuint typeHash);

	virtual void Render(GLfloat deltaTime);
	virtual void Update(GLfloat deltaTime);
};

#endif