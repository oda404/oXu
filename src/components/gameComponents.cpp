#include "gameComponents.hpp"

oxu::GameComponents::GameComponents() { }

oxu::GameComponents &oxu::GameComponents::getInstance()
{
    static GameComponents instance;
    return instance;
}

