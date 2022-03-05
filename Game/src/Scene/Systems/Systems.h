#pragma once

class Scene;

class Systems
{
  public:
    static void UpdatePosition(Scene &scene, int id, float deltaTime);

    static void UpdateRotation(Scene &scene, int id, float deltaTime);
};