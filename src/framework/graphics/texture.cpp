
#include<oxu/framework/graphics/texture.hpp>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/graphics/renderer.hpp>

namespace oxu::framework::graphics
{
using namespace framework;

    Texture::Texture(const std::string &path)
    {
        m_GL_tex = new opengl::Texture(path);
    }

    Texture::Texture() {  }

    Texture::~Texture()
    {
        delete m_GL_tex;
    }

    bool Texture::load(const std::string &path)
    {
        using namespace Renderer;
        std::uint8_t current_backend_enum = get_current_backend_enum();

        switch(current_backend_enum)
        {
        case Backends::OPENGL:
            m_GL_tex = new opengl::Texture(path);
            break;
        default:
            OXU_LOG_ERR("Tried to load a texture but current backend {} is unknown", current_backend_enum);
            return false;
        }

        return m_GL_tex ? true : false;
    }
}
