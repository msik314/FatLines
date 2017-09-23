#include "shader.h"
#include "debugUtils.h"
#include <cstring>
#include <cstdio>

#ifndef NDEBUG
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMessage);
#endif // NDEBUG

static GLuint createShader(const char* text, GLenum shaderType);


void Shader::init(const char* vertSrc, const char* fragSrc)
{
    //Create gpu program and shaders
    m_program = glCreateProgram();
	GLuint vertShader = createShader(vertSrc, GL_VERTEX_SHADER);
	GLuint fragShader = createShader(fragSrc, GL_FRAGMENT_SHADER);

    //attach shaders
	glAttachShader(m_program, vertShader);
	glAttachShader(m_program, fragShader);

    //Link shaders
	glLinkProgram(m_program);
	#ifndef NDEBUG
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed:\n");
    #endif // NDEBUG

    //Validate gpu program
	glValidateProgram(m_program);
	#ifndef NDEBUG
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid:\n");
	#endif // NDEBUG

    //Delete shaders because they are no longer needed
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
    //Delete gpu program
	glDeleteProgram(m_program);
}

#ifndef NDEBUG
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

    //Check for errors
	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

    //Get and print error messages if ther is an errror
	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		printf("%s: %s\n", errorMessage, error);
	}
}
#endif // NDEBUG

static inline  GLuint createShader(const char* text, GLenum shaderType)
{
    //Create shader
	GLuint shader = glCreateShader(shaderType);

    ASSERT(shader, "Error: shader creation failed\n");

	//Compile shader
	GLint len = strlen(text);

	glShaderSource(shader, 1, &text, &len);
	glCompileShader(shader);

    #ifndef NDEBUG
    //Error checking
    if(shaderType == GL_VERTEX_SHADER)
        checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Vertex shader compilation failed:\n");
    else if(shaderType == GL_FRAGMENT_SHADER)
        checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Fragment shader compilation failed:\n");
    else
        checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed:\n");
    #endif // NDEBUG

	return shader;
}
