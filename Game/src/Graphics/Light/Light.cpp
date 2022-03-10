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

void Light::ApplyLighting(float dot, Color &color, Face &face)
{
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    switch (m_light)
    {
    case Lights::BRIGHT:
        r = (float)color.r;
        g = (float)color.g;
        b = (float)color.b;
        break;

    case Lights::SHADOW:
        r = color.r * max(dot, 0.3f);
        g = color.g * max(dot, 0.3f);
        b = color.b * max(dot, 0.3f);
        break;

    case Lights::OUTLINE:
        r = color.r * max((1.0f - dot), 0.3f);
        g = color.g * max((1.0f - dot), 0.3f);
        b = color.b * max((1.0f - dot), 0.3f);
        break;
    }

    face.r = r / 255.0f;
    face.g = g / 255.0f;
    face.b = b / 255.0f;
}