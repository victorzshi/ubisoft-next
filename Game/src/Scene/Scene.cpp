#include "stdafx.h"

#include "Scene.h"

Scene::Scene() : viewport_({0.0f, 0.0f, 0.0f, 0.0f})
{
    // Initialize component arrays
}

Scene::~Scene()
{
    // Clean up stuff
}

void Scene::SetViewport(Box viewport)
{
    viewport_ = viewport;
}

void Scene::Render()
{
#ifdef _DEBUG
    DrawBorder();
#endif

    float x = viewport_.w * 0.01f;
    float y = viewport_.h * 0.95f;
    App::Print(x, y, "Scene::Render()");
}

void Scene::DrawBorder()
{
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
    float x = viewport_.x + 1.0f; // Offset into visible area
    float y = viewport_.y;
    float w = viewport_.w;
    float h = viewport_.h - 1.0f; // Offset into visible area
    App::DrawLine(x, y, x, h, r, g, b);
    App::DrawLine(x, h, w, h, r, g, b);
    App::DrawLine(w, h, w, y, r, g, b);
    App::DrawLine(w, y, x, y, r, g, b);
}