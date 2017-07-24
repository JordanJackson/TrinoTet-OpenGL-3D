#include "GameObject.h"

GameObject::GameObject() 
	: transform(new Transform()), components(std::multimap<GLuint, Component*>())
{

}

GameObject::GameObject(Transform* transform)
	: transform(transform), components(std::multimap<GLuint, Component*>())
{

}

GameObject::GameObject(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
	: transform(new Transform(position, rotation, scale)), components(std::multimap<GLuint, Component*>())
{

}

GameObject::~GameObject()
{
	delete transform;
}

void GameObject::AddComponent(Component* component)
{
	GLuint typeHash = typeid(component).hash_code();

	auto it = components.find(typeHash);
	if (it != components.end())
	{
		delete (*it).second;
	}
	component->gameObject = this;
	component->transform = this->transform;
	// add to map
	components.insert(std::pair<GLuint, Component*>(typeHash, component));
}

void GameObject::RemoveComponent(GLuint typeHash)
{
	auto it = components.find(typeHash);
	if (it != components.end())
	{
		delete (*it).second;
		components.erase(typeHash);
	}
}

Component* GameObject::GetComponentByType(GLuint typeHash)
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		if (typeid(it->second).hash_code() == typeHash)
		{
			return it->second;
		}
	}

	return nullptr;
}

void GameObject::Update(GLfloat deltaTime)
{
	for (auto component : components)
	{
		component.second->Update(deltaTime);
	}
}