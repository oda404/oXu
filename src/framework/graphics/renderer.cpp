

#include<memory>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/window.hpp>
#include<oxu/framework/graphics/renderer.hpp>
#include<oxu/framework/graphics/opengl/backend.hpp>
#include<oxu/framework/graphics/genericBackend.hpp>

namespace oxu::framework::graphics::renderer
{

using namespace framework;

static GenericBackend *g_backend = nullptr;
static BackendType g_backend_type;

BackendType get_backend_type()
{
    return g_backend_type;
}

bool init(
    BackendType backend_type,
    std::string config_dir_path
)
{
    g_backend_type = backend_type;

    switch(g_backend_type)
    {
    case BackendType::OPENGL:
        destroy();
        g_backend = new opengl::Backend();
        break;

    default:
        OXU_LOG_ERROR("Unknown backend type {}", g_backend_type);
        return false;
    }

    if(!g_backend)
        return false;

    return g_backend->init(
        window::get_native_window(), 
        config_dir_path
    );
}

void destroy()
{
    if(g_backend)
    {
        delete g_backend;
        g_backend = nullptr;
    }
}

void clear()
{
    g_backend->clear();
}

void render()
{
    g_backend->render(
        window::get_native_window()
    );
}

void copy_texture(
    const Vector2<float> &position, 
    const Vector2<float> &size, 
    const Texture &tex,
    float alpha
)
{
    g_backend->copy_texture(position, size, tex, alpha);
}

}