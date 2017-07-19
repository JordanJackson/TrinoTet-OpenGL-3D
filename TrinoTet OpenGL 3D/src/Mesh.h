#ifndef _SRC_MESH_H_
#define _SRC_MESH_H_

#include <vector>

class Mesh
{
private:
	GLuint VBO, VAO;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> indices;

public:
	Mesh();
	~Mesh();

	void Initialize();
};

#endif