#include "stdafx.h"

#include "Scene/Scene.h"

Scene scene;

void Init()
{
    scene.SetViewport({0.0f, 0.0f, 960.0f, 540.0f});
}

void Update(float deltaTime)
{
    // Do something...
}

void Render()
{
    scene.Render();
}

void Shutdown()
{
    // Do something...
}