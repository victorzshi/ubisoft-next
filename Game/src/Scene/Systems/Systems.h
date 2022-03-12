#pragma once

class Scene;

class Systems
{
  public:
    void MoveCamera(Scene &scene, int id);
    void RotateTowardsMouse(Scene &scene, int id);
    void RotateTowardsShip(Scene &scene, int id);
    void AccelerateShip(Scene &scene, int id);
    void ShootAtMouse(Scene &scene, int id);
    void ShootAtShip(Scene &scene, int id);
    void UpdatePosition(Scene &scene, int id);
    void AddRotation(Scene &scene, int id);
    void CheckBulletHit(Scene &scene, int id);
    void ApplyGravity(Scene &scene, int id);
    void LimitShipVelocity(Scene &scene, int id);
    void ChangeColor(Scene &scene, int id);
    void SpinPlanet(Scene &scene, int id);
    void CheckShipCollision(Scene &scene, int id);
};