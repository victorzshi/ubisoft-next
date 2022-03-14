#include "stdafx.h"

#include "Graphics/UI/UI.h"
#include "Math/Matrix/MatrixTest.cpp"
#include "Math/Vector3/Vector3Test.cpp"
#include "Scene/Scene.h"

// If you change these, also update AppSettings.h
const float SCREEN_WIDTH = 960.0f;
const float SCREEN_HEIGHT = 540.0f;

Scene scene;
UI ui;

void Init()
{
    Vector3Test::RunTests();
    MatrixTest::RunTests();
    scene.Init();
    ui.Init(&scene, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Update(float deltaTime)
{
    ui.HandleInput();

    if (ui.GetScreen() == Screen::NONE)
    {
        scene.Update(deltaTime);
    }
}

void Render()
{
    if (ui.GetScreen() == Screen::NONE || ui.GetScreen() == Screen::PAUSED)
    {
        scene.Render();
    }

    ui.Render();
}

void Shutdown()
{
    scene.Shutdown();
}