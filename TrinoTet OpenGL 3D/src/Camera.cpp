#include "Camera.h"

Camera::Camera(const glm::mat4& projectionMatrix)
	: projectionMatrix(projectionMatrix)
{

}

void Camera::ComputeViewMatrix()
{
	//std::cout << "Recomputing View Matrix" << '\n';
	viewMatrix = glm::lookAt(transform->GetPosition(), transform->GetPosition() + transform->Forward(), transform->Up());
	//viewMatrix = glm::mat4();
}

void Camera::Initialize()
{
	ComputeViewMatrix();
}