#include "stdafx.h"

#include "Systems.h"

#include "Scene/Scene.h"

void Systems::MoveShip(Scene &scene, int id)
{
    float deltaVelocity = scene.GetShips().DELTA_VELOCITY;

    Physics physics;
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        physics.velocity.x = +deltaVelocity;
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        physics.velocity.x = -deltaVelocity;
    }
    if (App::GetController().GetLeftThumbStickX() == 0.0f)
    {
        physics.velocity.x = 0.0f;
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        physics.velocity.y = +deltaVelocity;
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        physics.velocity.y = -deltaVelocity;
    }
    if (App::GetController().GetLeftThumbStickY() == 0.0f)
    {
        physics.velocity.y = 0.0f;
    }

    scene.SetPhysics(id, physics);
}

void Systems::ShootBullet(Scene &scene, int id)
{
    if (!App::IsKeyPressed(VK_LBUTTON))
    {
        return;
    }

    float current = scene.GetTime();
    float elapsed = scene.GetTimer(id).Elapsed(current);
    float cooldown = scene.GetShips().BULLET_COOLDOWN;

    if (elapsed > cooldown)
    {
        scene.GetBullets().CreateBullet(scene, id);

        scene.GetShips().ResetBulletCooldown(scene, id);
    }
}

void Systems::UpdatePosition(Scene &scene, int id)
{
    Physics physics = scene.GetPhysics(id);
    Transform transform = scene.GetTransform(id);

    transform.position += physics.velocity * scene.GetDeltaTime() / 1000.0f;

    float width = 7.0f;
    if (transform.position.x > width)
    {
        transform.position.x = -width;
    }
    else if (transform.position.x < -width)
    {
        transform.position.x = width;
    }

    float height = 4.0f;
    if (transform.position.y > height)
    {
        transform.position.y = -height;
    }
    else if (transform.position.y < -height)
    {
        transform.position.y = height;
    }

    scene.SetTransform(id, transform);
}

void Systems::AddRotation(Scene &scene, int id)
{
    Physics physics = scene.GetPhysics(id);
    Transform transform = scene.GetTransform(id);

    transform.rotation.x += physics.velocity.y;
    transform.rotation.y += -physics.velocity.x;
    transform.rotation.z += physics.velocity.z;

    transform.rotation.x = fmod(transform.rotation.x, 360.0f);
    transform.rotation.y = fmod(transform.rotation.y, 360.0f);
    transform.rotation.z = fmod(transform.rotation.z, 360.0f);

    scene.SetTransform(id, transform);
}

void Systems::CheckAsteroidCollision(Scene &scene, int id)
{
    for (auto &asteroid : scene.GetAsteroids().GetIds())
    {
        if (Collider::IsHit(scene, id, asteroid))
        {
            Health health;

            health = scene.GetHealth(id);
            health.points--;
            scene.SetHealth(id, health);

            health = scene.GetHealth(asteroid);
            health.points--;
            scene.SetHealth(asteroid, health);

            scene.GetParticles().CreateExplosion(scene, id);
        }
    }
}