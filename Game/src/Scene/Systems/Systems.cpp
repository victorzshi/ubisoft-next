#include "stdafx.h"

#include "Systems.h"

#include "Scene/Scene.h"

void Systems::AccelerateShip(Scene &scene, int id)
{
    float deltaAcceleration = scene.GetShips().DELTA_ACCELERATION;

    Physics physics = scene.GetPhysics(id);

    physics.acceleration = Vector3();
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        physics.acceleration.x = +deltaAcceleration;
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        physics.acceleration.x = -deltaAcceleration;
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        physics.acceleration.y = +deltaAcceleration;
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        physics.acceleration.y = -deltaAcceleration;
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

    float elapsed = scene.GetDeltaTime() / 1000.0f;

    physics.velocity += physics.acceleration * elapsed;
    transform.position += physics.velocity * elapsed;

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

    scene.SetPhysics(id, physics);
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

void Systems::ApplyGravity(Scene &scene, int id)
{
    Physics physics = scene.GetPhysics(id);

    // Assume world origin is center of gravity
    Vector3 to = Vector3();
    Vector3 from = scene.GetTransform(id).position;
    Vector3 direction;
    if (to - from != Vector3())
    {
        direction = (to - from).Normalize();
    }

    physics.acceleration += direction;

    scene.SetPhysics(id, physics);
}

void Systems::LimitShipVelocity(Scene &scene, int id)
{
    Physics physics = scene.GetPhysics(id);

    float max = scene.GetShips().MAX_VELOCITY;
    if (physics.velocity.LengthSquared() > max * max)
    {
        physics.velocity = physics.velocity.Normalize() * max;
    }

    scene.SetPhysics(id, physics);
}