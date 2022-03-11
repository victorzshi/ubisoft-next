#include "stdafx.h"

#include "Color.h"

#include "Math/Utils/Utils.h"

Color::Color() : r(255), g(255), b(255)
{
}

void Color::SetColor(Colors color)
{
    switch (color)
    {
    case Colors::WHITE:
        r = 255;
        g = 255;
        b = 255;
        break;

    case Colors::GREY:
        r = 128;
        g = 128;
        b = 128;
        break;

    case Colors::BLACK:
        r = 0;
        g = 0;
        b = 0;
        break;

    case Colors::RED:
        r = 255;
        g = 0;
        b = 0;
        break;

    case Colors::YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;

    case Colors::BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;

    case Colors::ORANGE:
        r = 255;
        g = 128;
        b = 0;
        break;

    case Colors::GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;

    case Colors::PURPLE:
        r = 128;
        g = 0;
        b = 255;
        break;

    case Colors::RANDOM:
        r = Utils::RandomInt(0, 255);
        g = Utils::RandomInt(0, 255);
        b = Utils::RandomInt(0, 255);
        break;
    }
}