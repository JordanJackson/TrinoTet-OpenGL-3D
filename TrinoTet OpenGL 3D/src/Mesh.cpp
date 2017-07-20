#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& rawVertices)
	: vertices(std::vector<Vertex>()), indices(std::vector<GLuint>())
{
	for (int i = 0; i < rawVertices.size(); i++)
	{
		std::vector<Vertex>::iterator it = std::find(vertices.begin(), vertices.end(), rawVertices[i]);
		if (it != vertices.end())
		{
			// no new vertex
			// add index of existing vertex
			auto idx = it - vertices.begin();
			indices.push_back((GLuint)idx);
		}
		else
		{
			// add new vertex
			vertices.push_back(rawVertices[i]);
			// add new index to last position
			indices.push_back(vertices.size() - 1);
		}
	}
	Initialize();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
	: vertices(vertices), indices(indices)
{
	Initialize();
}

Mesh::~Mesh()
{

}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//check_gl_error();
}

void Mesh::Initialize()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Vertex Array
	glBindVertexArray(VAO);
	// Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	check_gl_error();
	// Element (Index) Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	check_gl_error();
	// Bone Buffer

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	check_gl_error();
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normals));
	check_gl_error();
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
	check_gl_error();
	// Vertex Bone Data
	// Bone ID
	// Bone Weight
	
	// unbind VAO
	glBindVertexArray(0);
	check_gl_error();
}



