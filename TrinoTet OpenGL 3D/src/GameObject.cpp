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

	components.insert(std::pair<GLuint, Component*>(typeHash, component));

	IRenderable* renderable = dynamic_cast<IRenderable*>(component);
	if (renderable != nullptr)
	{
		auto itRen = renderables.find(typeHash);
		if (itRen != renderables.end())
		{
			delete (*itRen).second;
		}

		renderables.insert(std::pair<GLuint, IRenderable*>(typeHash, renderable));
	}
}

void GameObject::RemoveComponent(GLuint typeHash)
{
	auto it = components.find(typeHash);
	if (it != components.end())
	{
		IRenderable* renderable = dynamic_cast<IRenderable*>((*it).second);
		if (renderable != nullptr)
		{
			auto itRen = renderables.find(typeHash);
			if (itRen != renderables.end())
			{
				renderables.erase(typeHash);
			}
		}

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

void GameObject::Render(glm::mat4 view, glm::mat4 projection, GLfloat deltaTime)
{
	for (auto renderable : renderables)
	{
		renderable.second->Render(transform->GetMatrix(), view, projection, deltaTime);
	}
}

void GameObject::Update(GLfloat deltaTime)
{
	for (auto component : components)
	{
		component.second->Update(deltaTime);
	}
}