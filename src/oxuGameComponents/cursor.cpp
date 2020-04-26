#include"cursor.hpp"

oxu::Cursor::Cursor() { }

oxu::Cursor::~Cursor()
{
    SDL_DestroyTexture(cursorTex);
    cursorTex = NULL;
}

void oxu::Cursor::initTexture(SDL_Texture *p_cursorTex)
{
    cursorTex = p_cursorTex;

    if(SDL_QueryTexture(cursorTex, NULL, NULL, &cursorRect.w, &cursorRect.h) < 0)
    {
        logUtil.log(Log::WARNING, SDL_GetError());
    }
    else
    {
        halfTex.x = cursorRect.w / 2;
        halfTex.y = cursorRect.h / 2;
    }
}

SDL_Texture *oxu::Cursor::getTexture()
{
    return cursorTex;
}

const SDL_Rect *oxu::Cursor::getRect()
{
    return &cursorRect;
}

void oxu::Cursor::updatePos(const Vector2i &newPos)
{
    cursorRect.x = newPos.x - halfTex.x;
    cursorRect.y = newPos.y - halfTex.y;
}

