#include"cursor.hpp"

oxu::Cursor::Cursor() { }

oxu::Cursor::~Cursor()
{
    SDL_FreeCursor(customCursor);
    customCursor = NULL;
}

oxu::Cursor &oxu::Cursor::getInstance()
{
    static Cursor cursorInstance;
    return cursorInstance;
}

void oxu::Cursor::set(const std::string &skinPath)
{
    /* Load the image into a surface */
    SDL_Surface *surface = IMG_Load( (skinPath + "/cursor.png").c_str() );

    if(!surface)
    {
        LOG_WARN("Could not load cursor sprite: {0}", IMG_GetError());
    }

    /* Check to see if there is already a custom cursor loaded */
    if(customCursor)
    {
        SDL_FreeCursor(customCursor);
        customCursor = NULL;
    }
    /* Create the cursor */
    customCursor = SDL_CreateColorCursor(surface, surface->w / 2, surface->h / 2);

    /* Free the above loaded surface */
    SDL_FreeSurface(surface);

    /* Set the cursor */
    SDL_SetCursor(customCursor);
}
