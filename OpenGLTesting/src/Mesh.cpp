#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
	vertices = new std::vector<Vertex>;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, vertices->size());
	glDrawArrays(GL_TRIANGLES, 0, vertices->size());
	//glBindVertexArray(0);
}
void Mesh::AddVertex(Vertex vertex)
{
	vertices->push_back(vertex);
}
void Mesh::BuildVBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), vertices->data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

	glBindVertexArray(0);
}

