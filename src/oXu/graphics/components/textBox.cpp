#include"textBox.hpp"

namespace oxu
{
    void TextBox::createTexture(SDL_Renderer *targetRenderer, TTF_Font *font)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});

        rect.w = surface->w;
        rect.h = surface->h;

        // destroy texture to avoid mem leaks
        SDL_DestroyTexture(tex);
        tex = NULL;
        
        tex = SDL_CreateTextureFromSurface(targetRenderer, surface);

        SDL_FreeSurface(surface);
    }

    TextBox::~TextBox()
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
}