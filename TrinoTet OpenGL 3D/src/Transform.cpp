#include "Transform.h"

Transform::Transform()
	: position(glm::vec3(0.0f)), rotation(glm::quat()), scale(glm::vec3(1.0f)), dirtyFlag(true)
{
	ComputeMatrix(glm::mat4());
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale), dirtyFlag(true)
{
	ComputeMatrix(glm::mat4());
}

Transform::Transform(Transform* parent)
	: position(glm::vec3(0.0f)), rotation(glm::quat()), scale(glm::vec3(1.0f)), parent(parent), dirtyFlag(true)
{
	ComputeMatrix(parent->GetMatrix());
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale, Transform* parent)
	: position(position), rotation(rotation), scale(scale), parent(parent), dirtyFlag(true)
{
	ComputeMatrix(parent->GetMatrix());
}

Transform::~Transform()
{

}

void Transform::Update(GLfloat deltaTime)
{

}

void Transform::ComputeMatrix(const glm::mat4& parentMatrix)
{
	if (dirtyFlag)
	{
		//std::cout << "Recomputing Matrix" << '\n';
		matrix = parentMatrix;
		matrix = glm::translate(matrix, position);
		matrix *= glm::toMat4(rotation);
		matrix = glm::scale(matrix, scale);

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->ComputeMatrix(matrix);
		}

		dirtyFlag = false;
	}
}

void Transform::SetParent(Transform& parentTransform)
{
	parent = &parentTransform;
	parentTransform.AddChild(*this);
}

void Transform::AddChild(Transform& childTransform)
{
	children.push_back(&childTransform);
	childTransform.dirtyFlag = true;
	childTransform.ComputeMatrix(matrix);
}

void Transform::RemoveChild(Transform& childTransform)
{
	children.erase(std::remove(children.begin(), children.end(), &childTransform), children.end());
}

void Transform::DirtyChildren()
{
	for (auto child : children)
	{
		child->dirtyFlag = true;
	}
}

glm::mat4 Transform::GetMatrix()
{
	RecomputeCheck();
	return matrix;
}

void Transform::Translate(const glm::vec3& movement)
{
	position += movement;
	dirtyFlag = true;
	DirtyChildren();
}

void Transform::Rotate(float angle, const glm::vec3& axis)
{
	rotation *= glm::quat(axis * angle);
	dirtyFlag = true;
	DirtyChildren();
}

void Transform::Scale(float scalar)
{
	scale *= scalar;
	dirtyFlag = true;
	DirtyChildren();
}

glm::vec3 Transform::Forward()
{
	return rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 Transform::Right()
{
	return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Transform::Up()
{
	return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}