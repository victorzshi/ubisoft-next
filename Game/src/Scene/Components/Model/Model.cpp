#include "stdafx.h"

#include "Model.h"

Model::Model() : mesh(Mesh()), color(Color()), lighting(Lighting::BRIGHT)
{
}

void Model::ApplyLighting(float dot, Face &face)
{
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    switch (lighting)
    {
    case Lighting::BRIGHT:
        r = (float)color.r;
        g = (float)color.g;
        b = (float)color.b;
        break;

    case Lighting::SHADOW:
        r = color.r * max(dot, 0.3f);
        g = color.g * max(dot, 0.3f);
        b = color.b * max(dot, 0.3f);
        break;

    case Lighting::OUTLINE:
        r = color.r * max((1.0f - dot), 0.3f);
        g = color.g * max((1.0f - dot), 0.3f);
        b = color.b * max((1.0f - dot), 0.3f);
        break;
    }

    face.r = r / 255.0f;
    face.g = g / 255.0f;
    face.b = b / 255.0f;
}