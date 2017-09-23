#ifndef SHADER_H
#define SHADER_H

#include <gl/gl3w.h>
#include <glm/glm.hpp>

class Shader
{
public:
    //Default Constructor
    Shader(){}

    //Constructor takes vertex and fragment shader source code as strings
    Shader(const char* vertSrc, const char* fragSrc){init(vertSrc, fragSrc);}

    //Destructor
    ~Shader();

    void init(const char* vertSrc, const char* fragSrc);

    //Use the shader
    inline void bind(){glUseProgram(m_program);}

    //Update uniforms.  First argument is uniform location in shader.
    inline void uniform(int32_t location, int32_t value){glUniform1i(location, value);}
    inline void uniform(int32_t location, uint32_t value){glUniform1ui(location, value);}
    inline void uniform(int32_t location, float value){glUniform1f(location, value);}
    inline void uniform(int32_t location, const glm::ivec2& value){glUniform2i(location, value.x, value.y);}
    inline void uniform(int32_t location, const glm::uvec2& value){glUniform2ui(location, value.x, value.y);}
    inline void uniform(int32_t location, const glm::vec2& value){glUniform2f(location, value.x, value.y);}
    inline void uniform(int32_t location, const glm::ivec3& value){glUniform3i(location, value.x, value.y, value.z);}
    inline void uniform(int32_t location, const glm::uvec3& value){glUniform3ui(location, value.x, value.y, value.z);}
    inline void uniform(int32_t location, const glm::vec3& value){glUniform3f(location, value.x, value.y, value.z);}
    inline void uniform(int32_t location, const glm::ivec4& value){glUniform4i(location, value.x, value.y, value.z, value.w);}
    inline void uniform(int32_t location, const glm::uvec4& value){glUniform4ui(location, value.x, value.y, value.z, value.w);}
    inline void uniform(int32_t location, const glm::vec4& value){glUniform4f(location, value.x, value.y, value.z, value.w);}

    //Update Matrix Uniforms.  First argument is uniform location in shader.
    inline void uniformMat(int32_t location, const glm::mat2& value){glUniformMatrix2fv(location, 1, false, &value[0][0]);}
    inline void uniformMat(int32_t location, const glm::mat3& value){glUniformMatrix3fv(location, 1, false, &value[0][0]);}
    inline void uniformMat(int32_t location, const glm::mat4& value){glUniformMatrix4fv(location, 1, false, &value[0][0]);}

    //Update uniform arrays.  First argument is uniform location in shader.
    inline void uniformArray(int32_t location, const int32_t* pvalue, uint32_t count){glUniform1iv(location, count, pvalue);}
    inline void uniformArray(int32_t location, const uint32_t* pvalue, uint32_t count){glUniform1uiv(location, count, pvalue);}
    inline void uniformArray(int32_t location, const float* pvalue, uint32_t count){glUniform1fv(location, count, pvalue);}
    inline void uniformMatArray(int32_t location, const glm::mat4* pvalue, uint32_t count){glUniformMatrix4fv(location, count, false, (const float*)pvalue);}
private:
    GLuint m_program;
};
#endif // SHADER_H
