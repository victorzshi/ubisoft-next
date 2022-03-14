#include "stdafx.h"

#include "Graphics/UI/UI.h"
#include "Math/Matrix/MatrixTest.cpp"
#include "Math/Vector3/Vector3Test.cpp"
#include "Scene/Scene.h"

Scene scene;
Renderer renderer;
UI ui;

void Init()
{
    Vector3Test::RunTests();
    MatrixTest::RunTests();
    scene.Init(renderer);
    renderer.Init(scene);
    ui.Init(scene, renderer);
}

void Update(float deltaTime)
{
    ui.HandleInput();

    if (ui.GetScreen() == Screen::NONE)
    {
        ui.Update();
        scene.Update(deltaTime);
        renderer.Update(deltaTime);
    }
    if (ui.GetScreen() == Screen::PAUSED)
    {
        renderer.MoveCamera(deltaTime);
    }
}

void Render()
{
    if (ui.GetScreen() == Screen::NONE || ui.GetScreen() == Screen::PAUSED)
    {
        renderer.Render();
    }

    ui.Render();
}

void Shutdown()
{
}