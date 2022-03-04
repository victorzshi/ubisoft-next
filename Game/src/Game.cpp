#include "stdafx.h"

#include "Math/Matrix/MatrixTest.cpp"
#include "Math/Vector3/Vector3Test.cpp"
#include "Scene/Scene.h"

Scene scene;
std::string tests;

void Init()
{
    try
    {
        Vector3Test::RunTests();
        MatrixTest::RunTests();
        tests = "All tests passed!";
    }
    catch (const char *s)
    {
        tests = s;
    }
    scene.Init();
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