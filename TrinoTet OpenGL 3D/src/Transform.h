#ifndef _SRC_TRANSFORM_H_
#define _SRC_TRANSFORM_H_
#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"

class Transform : public Component
{
private:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::mat4 matrix;

	Transform* parent;
	std::vector<Transform*> children;

	bool dirtyFlag;

public:
	Transform();
	Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	Transform(Transform* parent);
	Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale, Transform* parent);
	~Transform();

	void Update(GLfloat deltaTime) override;

	void ComputeMatrix(const glm::mat4& parentMatrix);
	void SetParent(Transform& parentTransform);
	void AddChild(Transform& childTransform);
	void RemoveChild(Transform& childTransform);
	void DirtyChildren();

	void Translate(const glm::vec3& move);
	void Rotate(float angle, const glm::vec3& axis);
	void Scale(float factor);
	void Scale(const glm::vec3& scale);

	inline const glm::vec3& GetPosition() { RecomputeCheck(); return position; }
	inline void SetPosition(const glm::vec3& position) { this->position = position; }

	inline const glm::quat& GetRotation() { RecomputeCheck(); return rotation; }
	inline void SetRotation(const glm::quat& rotation) { this->rotation = rotation; }

	inline const glm::vec3& GetScale() { RecomputeCheck(); return scale; }
	inline void SetScale(const glm::vec3& scale) { this->scale = scale; }

	inline void RecomputeCheck() 
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

	glm::vec3 Forward();
	glm::vec3 Up();
	glm::vec3 Right();

	glm::mat4 GetMatrix();
};

#endif