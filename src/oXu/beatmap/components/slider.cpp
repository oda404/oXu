#include"slider.hpp"

namespace oxu
{
    Slider::Slider(
        const Vector2<float> &position_p,
        const std::uint32_t &hitTime_p,
        const std::uint8_t &type_p,
        const std::vector<Vector2<float>> &controlPoints_p,
        const char &sType_p,
        const int &repeats_p,
        const double &expectedLength_p,
        const Difficulty &difficulty_p
    ) : HitCircle(position_p, hitTime_p, type_p, difficulty_p)
    {
        controlPoints = controlPoints_p;
        sType = sType_p;
        repeats = repeats_p;
        expectedLength = expectedLength_p;
    }

    void Slider::update(const double &delta, const Difficulty &difficulty)
    {

    }

    void Slider::render(SDL_Renderer *targetRenderer, Skin *currentSkin)
    {

    }

    void Slider::setErrorMargin(const long double &err, const std::uint32_t &approachRateMs)
    {
        approachCircle.lerpT = (err - spawnTime) / approachRateMs;
    }

    bool Slider::shouldBeAddedToPool(const std::uint32_t &mapTimeMs)
    {
        if(mapTimeMs >= spawnTime)
        {
            return true;
        }

        return false;
    }

    bool Slider::shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs)
    {
        if(mapTimeMs > hitTime)
        {
            return true;
        }
        
        return false;
    }
}