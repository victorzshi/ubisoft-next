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
    scene.Init(renderer, ui);
    renderer.Init(scene);
    ui.Init(scene, renderer);
}

void Update(float deltaTime)
{
    ui.HandleInput();

    if (ui.GetScreen() == Screen::PAUSED || ui.GetScreen() == Screen::GAME_OVER)
    {
        renderer.MoveCamera(deltaTime);
    }

    if (ui.GetScreen() != Screen::PAUSED)
    {
        ui.Update();
        scene.Update(deltaTime);
        renderer.Update(deltaTime);
    }
}

void Render()
{
    renderer.Render();
    ui.Render();
}

void Shutdown()
{
}