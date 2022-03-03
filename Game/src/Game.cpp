#include "stdafx.h"

#include "Math/Vector3/Vector3Test.cpp"
#include "Scene/Scene.h"

Scene scene;
std::string tests;

void Init()
{
    try
    {
        Vector3Test::RunTests();
        tests = "All tests passed!";
    }
    catch (const char *s)
    {
        tests = s;
    }

    scene.Init({0.0f, 0.0f, 960.0f, 540.0f});
}

void Update(float deltaTime)
{
    scene.Update(deltaTime);
}

void Render()
{
    scene.Render();

#ifdef _DEBUG
    App::Print(10.0f, 100.0f, tests.c_str());
#endif
}

void Shutdown()
{
    // Do something...
}