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

        int createAndLinkProgram();

    public:
        Shader(const std::string &path);
        ~Shader();

        void setUniform1i(const std::string &name, int v0);
        void setUniform1f(const std::string &name, float v0);
        void bind() const;
        void unbind() const;
        void deleteProgram() const;
        const bool &isValid() const;
    };
}