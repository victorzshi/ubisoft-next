#pragma once

class Scene;

class Systems
{
  public:
    static void MoveShip(Scene &scene, int id);
    static void ShootBullet(Scene &scene, int id);
    static void UpdatePosition(Scene &scene, int id);
    static void AddRotation(Scene &scene, int id);
    static void CheckAsteroidCollision(Scene &scene, int id);
};