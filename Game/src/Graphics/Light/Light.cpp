#include "stdafx.h"

#include "Light.h"

#include "Graphics/Color/Color.h"
#include "Graphics/Face/Face.h"

Light::Light() : m_light(Lights::BRIGHT)
{
}

Lights Light::GetLight() const
{
    return m_light;
}

void Light::SetLight(Lights light)
{
    m_light = light;
}

void Light::AddLighting(float dot, Color &color, Face &face)
{
    switch (m_light)
    {
    case Lights::BRIGHT:
        face.r = (float)color.r;
        face.g = (float)color.g;
        face.b = (float)color.b;
        break;

    case Lights::SHADOW:
        face.r = color.r * max(dot, 0.3f);
        face.g = color.g * max(dot, 0.3f);
        face.b = color.b * max(dot, 0.3f);
        break;

    case Lights::OUTLINE:
        face.r = color.r * max((1.0f - dot), 0.3f);
        face.g = color.g * max((1.0f - dot), 0.3f);
        face.b = color.b * max((1.0f - dot), 0.3f);
        break;
    }

    face.r /= 255.0f;
    face.g /= 255.0f;
    face.b /= 255.0f;
}