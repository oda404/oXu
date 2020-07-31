#include"text.hpp"

namespace oxu
{
    TextBox::~TextBox()
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }

    bool Text::init()
    {
        if(TTF_Init() < 0)
        {
            StatusCodes::statusCode = StatusCodes::TTF_INIT_FAIL;
            LOG_ERR(TTF_GetError());
            return false;
        }

        font = TTF_OpenFont("res/fonts/Hack-Regular.ttf", 20);

        if(!font)
        {
            StatusCodes::statusCode = StatusCodes::FONT_LOAD_FAIL;
            LOG_ERR("Could not load font");
            return false;
        }

        return true;
    }

    void Text::createTexture(SDL_Renderer *renderer, TextBox &textBox)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, textBox.text.c_str(), {255, 255, 255});

        textBox.rect.w = surface->w;
        textBox.rect.h = surface->h;

        // destroy texture to avoid mem leaks
        SDL_DestroyTexture(textBox.tex);
        textBox.tex = NULL;
        
        textBox.tex = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
    }

    Text::~Text()
    {
        TTF_CloseFont(font);
        font = NULL;

        TTF_Quit();
    }
}