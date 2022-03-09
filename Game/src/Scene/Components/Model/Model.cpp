#include "stdafx.h"

#include "Model.h"

Model::Model() : mesh(Mesh()), color(Color()), light(Light::BRIGHT)
{
}

void Model::SetFaceColor(float dot, Face &face)
{
    switch (light)
    {
    case Light::BRIGHT:
        face.r = (float)color.r;
        face.g = (float)color.g;
        face.b = (float)color.b;
        break;

    case Light::SHADOW:
        face.r = color.r * max(dot, 0.3f);
        face.g = color.g * max(dot, 0.3f);
        face.b = color.b * max(dot, 0.3f);
        break;

    case Light::OUTLINE:
        face.r = color.r * max((1.0f - dot), 0.3f);
        face.g = color.g * max((1.0f - dot), 0.3f);
        face.b = color.b * max((1.0f - dot), 0.3f);
        break;
    }

    face.r /= 255.0f;
    face.g /= 255.0f;
    face.b /= 255.0f;
}
