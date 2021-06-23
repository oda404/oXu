
#include<oxu/framework/graphics/texture.hpp>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/graphics/renderer.hpp>

namespace oxu::framework::graphics
{
using namespace framework;
using namespace renderer;

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
        BackendType backend_type = 
        renderer::get_backend_type();

        switch(backend_type)
        {
        case BackendType::OPENGL:
            m_GL_tex = new opengl::Texture(path);
            break;
        default:
            OXU_LOG_ERROR("Tried to load a texture but current backend {} is unknown", backend_type);
            return false;
        }

        return m_GL_tex ? true : false;
    }
}
