#pragma once

class Scene;

class Systems
{
  public:
    static void ProcessInput(Scene &scene, int id);
    static void UpdatePosition(Scene &scene, int id, float deltaTime);
    static void AddRotation(Scene &scene, int id, float deltaTime);
};