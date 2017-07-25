#ifndef _SRC_MESHRENDERER_H_
#define _SRC_MESHRENDERER_H_
#pragma once

#include "Mesh.h"
#include "IRenderable.h"

class MeshRenderer : public IRenderable
{
private:
	Mesh* mesh;

public:
	MeshRenderer(Material& material, Mesh& mesh);
	~MeshRenderer();

	virtual void Render(glm::mat4 view, glm::mat4 projection) override;
	virtual void Update(GLfloat deltaTime) override;
};

#endif