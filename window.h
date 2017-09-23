#ifndef WINDOW_H
#define WINDOW_H

#include<gl/gl3w.h>
#include<glfw/glfw3.h>

class Window
{
public:
	Window(int32_t width, int32_t height, const char* title)
	{
		m_width = width;
		m_height = height;

		//Initialize GLFW
		glfwInit();

		//Create Window
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //Major Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Minor Version
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, false);

		m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);

		//OpenGL context
		glfwMakeContextCurrent(m_window);

		//Load OpenGL
		gl3wInit();

		//Initialize viewport
		glViewport(0, 0, width, height);
	}

	~Window()
	{
		//Closes window and terminates GLFW
		glfwTerminate();
	}
	
	//Sets window close flag
    inline void close(){glfwSetWindowShouldClose(m_window, true);}

    //Swaps window frame buffers
    inline void swapBuffers(){glfwSwapBuffers(m_window);}

    //Clears the screen to the specified color
    inline void clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    //Get window parameters
    inline int32_t getWidth(){return m_width;}
    inline int32_t getHeight(){return m_height;}
    inline GLFWwindow* getWindow(){return m_window;}

private:
    int32_t m_width;
    int32_t m_height;
    GLFWwindow* m_window;
};

#endif //WINDOW_H