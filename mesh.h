#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

class Mesh
{
public:
    //Constructor takes a vertex array and an index array for indexed drawing
    Mesh()
	{
		glm::vec2 vertices[4] = {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}};
		uint8_t indices[6] = {0, 1, 2, 2, 3, 0};
		
		//Number of vertices to draw
		m_drawCount = 6;

		//Generate vertex array object
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		//generate vertex buffers
		glGenBuffers(2, m_vab);

		//Set up vertex data
		glBindBuffer(GL_ARRAY_BUFFER, m_vab[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,  GL_STATIC_DRAW);

		//Set up vertex attributes w
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

		//Set up index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vab[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	~Mesh()
	{
		//Delete buffer and vertex arrays
		glDeleteBuffers(2, m_vab);
		glDeleteVertexArrays(1, &m_vao);
	}


    //Instanced draw call defaults to 1 instance if no argument is given
    inline void draw(uint32_t instances = 1)
    {
        glBindVertexArray(m_vao);
        glDrawElementsInstanced(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_BYTE, NULL, instances);
    }

private:
    GLuint m_vao;
    GLuint m_vab[2];

    GLuint m_drawCount;
};

#endif //MESH_H