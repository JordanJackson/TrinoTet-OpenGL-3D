#ifndef _SRC_MESHRENDERER_H_
#define _SRC_MESHRENDERER_H_

#include "Component.h"
#include "Material.h"
#include "Mesh.h"


class MeshRenderer : public Component
{
private:
	Material material;
	Mesh mesh;

public:
	MeshRenderer();
	~MeshRenderer();

	void Update(GLfloat deltaTime) override;
};

#endif