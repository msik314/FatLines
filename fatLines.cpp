#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#define SHADER_DATA
#include "shaderData.h"
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <thread>
#include <cmath>

int gcd(int a, int b)
{
	return b == 0 ? a : gcd (b, a % b); 
}

int max(int a, int b)
{
	return b > a ? b : a;
}

int abs(int a)
{
	return a >= 0 ? a : -a;
}

void drawLine(glm::ivec2 start, glm::ivec2 end, int weight, Shader* shader, Mesh* mesh)
{
	weight = 2 * (weight / 2);
	if (weight == 0)
	{
		return;
	}
	
	Transform transform;
	
	if(start.y == end.y)
	{
		transform.getScale() = glm::vec2(end.x - start.x, weight);
		transform.getPos() = glm::vec2((start.x + end.x) / 2.0f , (start.y + end.y) / 2.0f);
		shader->uniformMat(0, glm::ortho(-32.0f, 32.0f, -18.0f, 18.0f) * transform.getModel());
		mesh->draw();
		return;
	}
	
	glm::mat4 vp = glm::ortho(-32.0f, 32.0f, -18.0f, 18.0f);
	
	int x = start.x;
	int y = start.y;
	glm::ivec2 slope = glm::ivec2(end.x - start.x, end.y - start.y);
	slope /= gcd(slope.x, slope.y);
	int lineWidth = max(weight, max(weight * slope.x/slope.y, weight * 0.75f * (slope.x/slope.y + 1)));
	int p = 0;
	int di = slope.x / slope.y;
	int dp = slope.x % slope.y;
	while(y < end.y)
	{
		transform.getScale() = glm::vec2(lineWidth, 1);
		transform.getPos() = glm::vec2(x, y + 0.5f);
		shader->uniformMat(0, vp * transform.getModel());
		mesh->draw();
		
		x += di;
		p += dp;
		if(p >= slope.y)
		{
			p -= slope.y;
			x += 1;
		}
		y += 1;
	}
}

int main()
{
	Window window(1280, 720, "Fat Line");
	Mesh mesh;
	Shader shader(rectVert, rectFrag);
	
	shader.bind();
	shader.uniform(1, glm::vec4(0, 1, 0, 1));
	
	double lastTime = 0;
	const double delta = 1.0f/60;
	glfwSetTime(0);
	while(!glfwWindowShouldClose(window.getWindow()))
	{
		glfwPollEvents();
		
		window.clear(0, 0, 0, 1);
		
		glm::dvec2 mousePos;
		glfwGetCursorPos(window.getWindow(), &mousePos.x, &mousePos.y);
		
		mousePos /= window.getHeight();
		mousePos *= 36;
		mousePos -= glm::dvec2(32, 18);
		
		glm::ivec2 end = glm::ivec2((int)floor(mousePos.x), (int)floor(-mousePos.y));
		/*if (end.y + 18 > end.x + 32)
		{
			int temp = end.x + 14;
			end.x = end.y - 14;
			end.y = temp;
		}*/
		
		drawLine(glm::ivec2(-32, -18), end, 4, &shader, &mesh);
		
		window.swapBuffers();
		
		std::this_thread::sleep_for(std::chrono::duration<double>(delta + glfwGetTime() - lastTime));
		lastTime = glfwGetTime();
	}
	
	return 0;
}