
#include<stdio.h>
#include<cstdint>
#include<string.h>
#include<sstream>
#include<oxu/framework/graphics/opengl/shader.hpp>
#include<oxu/framework/graphics/opengl/core.hpp>
#include<oxu/framework/graphics/shader_type.hpp>
#include<oxu/framework/logger.hpp>

#define FILE_BUFF_MAX_SIZE 64

namespace oxu::framework::graphics::opengl
{
    
using namespace framework;

    static int parse_shaders(const std::string &path, ShadersInfo &sInfo)
    {
        FILE *file = fopen(path.c_str(), "r");

        if(!file)
        {
            OXU_LOG_WARN("[OpenGL] Couldn't open shader: {}", path);
            return 1;
        }

        char buff[FILE_BUFF_MAX_SIZE];
        ShaderType currentShader = ShaderType::INVALID;

        while(fgets(buff, FILE_BUFF_MAX_SIZE, file))
        {
            if(buff[0] == '/' && buff[1] == '/')
            {
                if(strstr(buff, "//VERTEX_SHADER"))
                {
                    currentShader = ShaderType::GL_VERTEX;
                }
                else if(strstr(buff, "//FRAGMENT_SHADER"))
                {
                    currentShader = ShaderType::GL_FRAGMENT;
                }
            }
            else if(currentShader != ShaderType::INVALID)
            {
                switch(currentShader)
                {
                case ShaderType::GL_VERTEX:
                    sInfo.vertexSource += buff;
                    break;
                case ShaderType::GL_FRAGMENT:
                    sInfo.fragmentSource += buff;
                    break;

                default:
                    __builtin_unreachable();
                    break;
                }
            }
        }

        fclose(file);

        return 0;
    }

    static unsigned int compile_shader(unsigned int type, const std::string &source)
    {
        unsigned int shader_id;
        GL_CALL_ASSERT(shader_id = glCreateShader(type));

        const char *c_str_source = source.c_str();

        GL_CALL_ASSERT(glShaderSource(shader_id, 1, &c_str_source, nullptr));
        GL_CALL_ASSERT(glCompileShader(shader_id));

        int compile_status = 0;
        GL_CALL_ASSERT(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status));

        if(!compile_status)
        {
            int log_buff_len = 0;
            GL_CALL_ASSERT(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_buff_len));

            char *log_buff = new char[log_buff_len + 1];

            GL_CALL_ASSERT(glGetShaderInfoLog(shader_id, log_buff_len, nullptr, log_buff));
            OXU_LOG_WARN("[OpenGL] {}", log_buff);

            delete[] log_buff;
        }

        return shader_id;
    }

    static int get_uniform_location(const unsigned int &id, const std::string &name)
    {
        int loc = -1;
        GL_CALL_LOG(loc = glGetUniformLocation(id, name.c_str()));
        return loc;
    }

    static void print_shader_info_log()
    {

    }

    static void print_program_info_log(unsigned int &id)
    {
        int log_buff_len = 0;
        GL_CALL_ASSERT(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_buff_len));

        char *log_buff = new char[log_buff_len + 1];

        GL_CALL_ASSERT(glGetProgramInfoLog(id, log_buff_len, nullptr, log_buff));
        OXU_LOG_WARN("[OpenGL] {}", log_buff);

        delete[] log_buff;
    }

    Shader::Shader(const std::string &path)
    {
        if(parse_shaders(path, m_shadersInfo) != 0)
            return;

        m_shadersInfo.vertexId = compile_shader(GL_VERTEX_SHADER, m_shadersInfo.vertexSource);
        m_shadersInfo.fragmentId = compile_shader(GL_FRAGMENT_SHADER, m_shadersInfo.fragmentSource);

        createAndLinkProgram();
    }

    Shader::~Shader()
    {
        deleteProgram();
    }

    int Shader::createAndLinkProgram()
    {
        GL_CALL_ASSERT(m_id = glCreateProgram());

        GL_CALL_ASSERT(glAttachShader(m_id, m_shadersInfo.vertexId));
        GL_CALL_ASSERT(glAttachShader(m_id, m_shadersInfo.fragmentId));

        GL_CALL_ASSERT(glLinkProgram(m_id));

        int link_status = 0;
        GL_CALL_ASSERT(glGetProgramiv(m_id, GL_LINK_STATUS, &link_status));

        if(!link_status)
        {
            m_programValid = false;
            print_program_info_log(m_id);
            deleteProgram();
            return 1;
        }
        
        GL_CALL_ASSERT(glValidateProgram(m_id));

        /* Check m_id validity */
        int validate_status = 0;
        GL_CALL_ASSERT(glGetProgramiv(m_id, GL_VALIDATE_STATUS, &validate_status));
        if(!validate_status)
        {
            m_programValid = false;
            print_program_info_log(m_id);
            deleteProgram();
            return 2;
        }

        m_programValid = true;
        glDetachShader(m_id, m_shadersInfo.vertexId);
        glDetachShader(m_id, m_shadersInfo.fragmentId);

        return 0;
    }

    void Shader::setUniform1i(const std::string &name, int v0)
    {
        GL_CALL_ASSERT(glUniform1i(get_uniform_location(m_id, name), v0));
    }

    void Shader::setUniform1f(const std::string &name, float v0)
    {
        GL_CALL_ASSERT(glUniform1f(get_uniform_location(m_id, name), v0));
    }

    const bool &Shader::isValid() const
    {
        return m_programValid;
    }

    void Shader::bind() const
    {
        glUseProgram(m_id);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::deleteProgram() const
    {
        GL_CALL_ASSERT(glDeleteShader(m_shadersInfo.vertexId));
        GL_CALL_ASSERT(glDeleteShader(m_shadersInfo.fragmentId));
        GL_CALL_ASSERT(glDeleteProgram(m_id));
    }
}
