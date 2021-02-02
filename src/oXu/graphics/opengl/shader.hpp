#pragma once

#include<string>

namespace oxu::graphics::opengl
{
    struct ShadersInfo
    {
        std::string vertexSource;
        unsigned int vertexId;

        std::string fragmentSource;
        unsigned int fragmentId;
    };

    class Shader
    {
    private:
        bool m_programValid = false;
        unsigned int m_id;
        ShadersInfo m_shadersInfo;

        void createAndLinkProgram();

    public:
        Shader(const std::string &path);
        ~Shader();

        void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
        void setUniform1i(const std::string &name, int v0);
        void bind() const;
        void unbind() const;
        void deleteProgram() const;
        const bool &isValid() const;
    };
}