#include "stdafx.h"

#include "Model.h"

Model::Model() : mesh(Mesh()), color(Color::WHITE), light(Light::BRIGHT)
{
}

void Model::SetColor(float dot, Face &face)
{
    int r = 0;
    int g = 0;
    int b = 0;

    switch (color)
    {
    case Color::WHITE:
        r = 255;
        g = 255;
        b = 255;
        break;

    case Color::GREY:
        r = 128;
        g = 128;
        b = 128;
        break;

    case Color::BLACK:
        r = 0;
        g = 0;
        b = 0;
        break;

    case Color::RED:
        r = 255;
        g = 0;
        b = 0;
        break;

    case Color::YELLOW:
        r = 255;
        g = 255;
        b = 0;
        break;

    case Color::BLUE:
        r = 0;
        g = 0;
        b = 255;
        break;

    case Color::ORANGE:
        r = 255;
        g = 128;
        b = 0;
        break;

    case Color::GREEN:
        r = 0;
        g = 255;
        b = 0;
        break;

    case Color::PURPLE:
        r = 128;
        g = 0;
        b = 255;
        break;
    }

    switch (light)
    {
    case Light::BRIGHT:
        face.r = (float)r;
        face.g = (float)g;
        face.b = (float)b;
        break;

    case Light::SHADOW:
        face.r = r * max(dot, 0.3f);
        face.g = g * max(dot, 0.3f);
        face.b = b * max(dot, 0.3f);
        break;

    case Light::OUTLINE:
        face.r = r * max((1.0f - dot), 0.3f);
        face.g = g * max((1.0f - dot), 0.3f);
        face.b = b * max((1.0f - dot), 0.3f);
        break;
    }

    face.r /= 255.0f;
    face.g /= 255.0f;
    face.b /= 255.0f;
}
