#ifndef _SRC_MESHRENDERER_H_
#define _SRC_MESHRENDERER_H_
#pragma once

#include "Component.h"
#include "IRenderable.h"
#include "Material.h"
#include "Mesh.h"


class MeshRenderer : public Component, public IRenderable
{
private:
	Material* material;
	Mesh* mesh;

public:
	MeshRenderer();
	MeshRenderer(Material& material, Mesh& mesh);
	~MeshRenderer();

	virtual void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, GLfloat deltaTime) override;
	virtual void Update(GLfloat deltaTime) override;
};

#endif