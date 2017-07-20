#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::MeshRenderer(Material& material, Mesh& mesh)
	: material(&material), mesh(&mesh)
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Render(GLfloat deltaTime)
{
	material->SetActive();
	mesh->Draw();
}

void MeshRenderer::Update(GLfloat deltaTime)
{

}