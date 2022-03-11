#pragma once

class Scene;

class Systems
{
  public:
    void RotateTowardsMouse(Scene &scene, int id);
    void RotateTowardsShip(Scene &scene, int id);
    void AccelerateShip(Scene &scene, int id);
    void ShootBullet(Scene &scene, int id);
    void UpdatePosition(Scene &scene, int id);
    void AddRotation(Scene &scene, int id);
    void CheckBulletHit(Scene &scene, int id);
    void ApplyGravity(Scene &scene, int id);
    void LimitShipVelocity(Scene &scene, int id);
};