#include"shader.hpp"

#include<stdio.h>
#include<cstdint>
#include<string.h>
#include<sstream>

#include<oXu/graphics/opengl/core.hpp>
#include<oXu/core/logger.hpp>

#define FILE_BUFF_MAX_SIZE 64

namespace oxu::OpenGL
{
    enum ShaderTypes
    {
        VERTEX = 0,
        FRAGMENT = 1,
    };

    static void parseShaders(const std::string &path, ShadersInfo &sInfo)
    {
        FILE *file = fopen(path.c_str(), "r");

        if(!file)
        {
            OXU_LOG_WARN("Can't open shader file {}", path);
            return;
        }

        char buff[FILE_BUFF_MAX_SIZE];
        int8_t currentShader = -1;
        std::stringstream ss[2];

        while(fgets(buff, FILE_BUFF_MAX_SIZE, file))
        {
            if(buff[0] == '/' && buff[1] == '/')
            {
                if(strstr(buff, "//VERTEX_SHADER"))
                {
                    currentShader = ShaderTypes::VERTEX;
                }
                else if(strstr(buff, "//FRAGMENT_SHADER"))
                {
                    currentShader = ShaderTypes::FRAGMENT;
                }
            }
            else if(currentShader > -1)
            {
                ss[currentShader] << buff;
            }
        }

        fclose(file);

        sInfo.vertexSource = ss[ShaderTypes::VERTEX].str();
        sInfo.fragmentSource = ss[ShaderTypes::FRAGMENT].str();
    }

    static unsigned int compileShader(unsigned int type, const std::string &source)
    {
        unsigned int shaderId = glCreateShader(type);
        const char *cStrSource = source.c_str();

        glShaderSource(shaderId, 1, &cStrSource, NULL);
        glCompileShader(shaderId);

        int compileStatus = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

        if(!compileStatus)
        {
            int logSize = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

            char *logMsgBuff = new char[logSize];

            glGetShaderInfoLog(shaderId, logSize, nullptr, logMsgBuff);
            OXU_LOG_WARN(logMsgBuff);

            delete[] logMsgBuff;
        }

        return shaderId;
    }

    static int getUniformLocation(const unsigned int &m_id, const std::string &name)
    {
        int loc = -1;
        oxu_glCall_Log(loc = glGetUniformLocation(m_id, name.c_str()));
        return loc;
    }

    Shader::Shader(const std::string &path)
    {
        parseShaders(path, m_shadersInfo);

        m_shadersInfo.vertexId = compileShader(GL_VERTEX_SHADER, m_shadersInfo.vertexSource);
        m_shadersInfo.fragmentId = compileShader(GL_FRAGMENT_SHADER, m_shadersInfo.fragmentSource);

        createAndLinkProgram();
    }

    Shader::~Shader()
    {
        deleteProgram();
    }

    void Shader::createAndLinkProgram()
    {
        oxu_glCall_Assert(m_id = glCreateProgram());

        /* Attach shaders */
        oxu_glCall_Log(glAttachShader(m_id, m_shadersInfo.vertexId));
        oxu_glCall_Log(glAttachShader(m_id, m_shadersInfo.fragmentId));

        /* Link m_id */
        oxu_glCall_Log(glLinkProgram(m_id));

        /* Check m_id link status */
        int linked = 0;
        glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
        if(!linked)
        {
            m_programValid = false;

            int logSize = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logSize);

            char *logMsgBuff = new char[logSize];

            glGetProgramInfoLog(m_id, logSize, nullptr, logMsgBuff);
            OXU_LOG_WARN(logMsgBuff);

            deleteProgram();

            delete[] logMsgBuff;
        }
        
        oxu_glCall_Log(glValidateProgram(m_id));

        /* Check m_id validity */
        int valid = 0;
        glGetProgramiv(m_id, GL_VALIDATE_STATUS, &valid);
        if(!valid)
        {
            m_programValid = false;

            int logSize = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logSize);

            char *logMsgBuff = new char[logSize];

            glGetProgramInfoLog(m_id, logSize, nullptr, logMsgBuff);
            OXU_LOG_WARN(logMsgBuff);

            deleteProgram();

            delete[] logMsgBuff;
        }

        if(linked && valid)
        {
            m_programValid = true;
            glDetachShader(m_id, m_shadersInfo.vertexId);
            glDetachShader(m_id, m_shadersInfo.fragmentId);
        }
    }

    void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
    {
        oxu_glCall_Log(glUniform4f(getUniformLocation(m_id, name), v0, v1, v2, v3));
    }

    void Shader::setUniform1i(const std::string &name, int v0)
    {
        oxu_glCall_Log(glUniform1i(getUniformLocation(m_id, name), v0));
    }

    const bool &Shader::isValid() const
    {
        return m_programValid;
    }

    void Shader::bind() const
    {
        oxu_glCall_Assert(glUseProgram(m_id));
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::deleteProgram() const
    {
        oxu_glCall_Assert(glDeleteShader(m_shadersInfo.vertexId));
        oxu_glCall_Assert(glDeleteShader(m_shadersInfo.fragmentId));
        oxu_glCall_Assert(glDeleteProgram(m_id));
    }
}