#include "stdafx.h"

#include "Math/Matrix/MatrixTest.cpp"
#include "Math/Vector3/Vector3Test.cpp"
#include "Scene/Scene.h"

Scene scene;

void Init()
{
    Vector3Test::RunTests();
    MatrixTest::RunTests();
    scene.Init();
}

void Update(float deltaTime)
{
    scene.Update(deltaTime);
}

void Render()
{
    scene.Render();
}

void Shutdown()
{
    // TODO: This is causing a crash?
    // scene.Shutdown();
}