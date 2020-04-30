#include"cursor.hpp"

oxu::Cursor::Cursor() { }

oxu::Cursor::~Cursor()
{
    SDL_FreeCursor(customCursor);
    customCursor = NULL;
}

void oxu::Cursor::init()
{
    /* Load the image into a surface */
    SDL_Surface *surface = IMG_Load("skins/cursor.png");
    if(!surface)
    {

    }

    /* Create the cursor */
	customCursor = SDL_CreateColorCursor(surface, surface->w / 2, surface->h / 2);
    if(!customCursor)
    {

    }

    /* Free the above loaded surface */
	SDL_FreeSurface(surface);

    /* Set the cursor */
	SDL_SetCursor(customCursor);
}
