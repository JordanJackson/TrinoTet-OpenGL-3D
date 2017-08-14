#include "Transform.h"

Transform::Transform()
	: localPosition(glm::vec3(0.0f)), localRotation(glm::quat()), localScale(glm::vec3(1.0f)), dirtyFlag(true)
{
	ComputeMatrix(glm::mat4());
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
	: localPosition(position), localRotation(rotation), localScale(scale), dirtyFlag(true)
{
	ComputeMatrix(glm::mat4());
}

Transform::Transform(Transform* parent)
	: localPosition(glm::vec3(0.0f)), localRotation(glm::quat()), localScale(glm::vec3(1.0f)), parent(parent), dirtyFlag(true)
{
	ComputeMatrix(parent->GetMatrix());
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale, Transform* parent)
	: localPosition(position), localRotation(rotation), localScale(scale), parent(parent), dirtyFlag(true)
{
	ComputeMatrix(parent->GetMatrix());
}

Transform::~Transform()
{

}

void Transform::Update(GLfloat deltaTime)
{
	if (dirtyFlag)
	{
		if (parent == nullptr)
		{
			ComputeMatrix(glm::mat4());
		}
		else
		{
			ComputeMatrix(parent->GetMatrix());
		}
	}
}

void Transform::ComputeMatrix(const glm::mat4& parentMatrix)
{
	if (dirtyFlag)
	{
		//std::cout << "Recomputing Matrix" << '\n';
		matrix = parentMatrix;
		matrix = glm::translate(matrix, localPosition);
		matrix *= glm::toMat4(localRotation);
		matrix = glm::scale(matrix, localScale);

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->ComputeMatrix(matrix);
		}

		dirtyFlag = false;
	}
}

void Transform::SetParent(Transform& parentTransform)
{
	if (parent != nullptr)
	{
		localPosition += parent->GetPosition();
		localRotation *= parent->GetRotation();
		localScale *= parent->GetScale();
	}

	parent = &parentTransform;
	localPosition -= parent->GetPosition();
	localRotation *= glm::inverse(parent->GetRotation());
	localScale /= parent->GetScale();
	parentTransform.AddChild(*this);
}

void Transform::ClearParent()
{
	if (parent == nullptr)
	{
		return;
	}
	localScale *= parent->GetScale();
	localRotation *= parent->GetRotation();
	localPosition += parent->GetPosition();

	parent->RemoveChild(*this);
	parent = nullptr;
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
	localPosition += movement;
	dirtyFlag = true;
	DirtyChildren();
}

void Transform::Rotate(float angle, const glm::vec3& axis)
{
	localRotation *= glm::quat(axis * angle);
	dirtyFlag = true;
	DirtyChildren();
}

void Transform::Scale(float scalar)
{
	localScale *= scalar;
	dirtyFlag = true;
	DirtyChildren();
}

glm::vec3 Transform::Forward()
{
	return localRotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 Transform::Right()
{
	return localRotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Transform::Up()
{
	return localRotation * glm::vec3(0.0f, 1.0f, 0.0f);
}