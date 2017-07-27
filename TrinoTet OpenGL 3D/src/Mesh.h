#ifndef _SRC_MESH_H_
#define _SRC_MESH_H_
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <iostream>
#include <vector>

#include "GLDebugger.h"

struct Vertex
{
	glm::vec3 Positions;
	glm::vec3 Normals;
	glm::vec2 TexCoords;

	Vertex(glm::vec3 positions, glm::vec3 normals, glm::vec2 texCoords)
	{
		Positions = positions;
		Normals = normals;
		TexCoords = texCoords;
	}

	bool operator==(const Vertex& other)
	{
		return Positions == other.Positions && Normals == other.Normals && TexCoords == other.TexCoords;
	}
};

class Mesh
{
private:
	GLuint VBO, VAO, EBO;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Mesh() = default;
	Mesh(std::vector<Vertex>& vertices);
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	Mesh(const aiMesh& assimpMesh);
	~Mesh();

	void Draw();

private:
	void Initialize();
};

#endif