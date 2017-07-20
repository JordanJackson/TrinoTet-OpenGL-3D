#ifndef _SRC_GAMEOBJECT_H_
#define _SRC_GAMEOBJECT_H_
#pragma once

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Component.h"
#include "Mesh.h"
#include "IRenderable.h"
#include "Transform.h"

class GameObject
{
private:
	std::multimap<GLuint, Component*> components;
	std::multimap<GLuint, IRenderable*> renderables;

public:
	Transform* transform;

public:
	GameObject();
	GameObject(Transform* transform);
	GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	~GameObject();

	void AddComponent(Component* component);
	void RemoveComponent(GLuint typeHash);

	Component* GetComponentByType(GLuint typeHash);

	virtual void Render(glm::mat4 view, glm::mat4 projection, GLfloat deltaTime);
	virtual void Update(GLfloat deltaTime);
};

#endif