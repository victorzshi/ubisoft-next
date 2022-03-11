#pragma once

class Scene;

class Systems
{
  public:
    void MoveShip(Scene &scene, int id);
    void ShootBullet(Scene &scene, int id);
    void UpdatePosition(Scene &scene, int id);
    void AddRotation(Scene &scene, int id);
    void CheckAsteroidCollision(Scene &scene, int id);
};