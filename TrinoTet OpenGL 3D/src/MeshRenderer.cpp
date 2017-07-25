#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Material& material, Mesh& mesh)
	: IRenderable(material), mesh(&mesh)
{
	//std::cout << "MeshRenderer: " << material.shader->ID << std::endl;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Render(glm::mat4 view, glm::mat4 projection)
{
	//std::cout << "MeshRenderer Render: " << material->shader->ID << std::endl;
	Shader s = material->SetActive();
	glUniformMatrix4fv(glGetUniformLocation(s.ID, "model"), 1, GL_FALSE, glm::value_ptr(transform->GetMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(s.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(s.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	mesh->Draw();
}

void MeshRenderer::Update(GLfloat deltaTime)
{

}