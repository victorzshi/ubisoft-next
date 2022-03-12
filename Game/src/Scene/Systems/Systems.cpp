#include "stdafx.h"

#include "Systems.h"

#include "Scene/Scene.h"

#include "Math/Utils/Utils.h"

void Systems::RotateTowardsMouse(Scene &scene, int id)
{
    Transform transform = scene.GetTransform(id);

    Vector3 from = transform.up;
    Vector3 to = scene.GetMousePosition() - transform.position;

    transform.rotation.z = Utils::Angle(from, to);

    scene.SetTransform(id, transform);
}

void Systems::RotateTowardsShip(Scene &scene, int id)
{
    AI ai = scene.GetAI(id);
    Transform transform = scene.GetTransform(id);

    for (auto &ship : scene.GetShips().GetIds())
    {
        Vector3 shipPosition = scene.GetTransform(ship).position;

        if (Utils::Distance(transform.position, shipPosition) < ai.attackRange)
        {
            Vector3 from = transform.up;
            Vector3 to = shipPosition - transform.position;

            transform.rotation.y = 180.0f;
            transform.rotation.x = -90.0f;
            transform.rotation.z = Utils::Angle(from, to);

            break;
        }
        else
        {
            transform.rotation.x = 0.0f;
            transform.rotation.z = 0.0f;
            transform.rotation.y += scene.GetDeltaTime() / 10.0f;
            transform.rotation.y = fmod(transform.rotation.y, 360.0f);
        }
    }

    scene.SetTransform(id, transform);
}

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

void Systems::ShootAtMouse(Scene &scene, int id)
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
        Vector3 from = scene.GetTransform(id).position;
        Vector3 to = scene.GetMousePosition();

        scene.GetBullets().ShootAt(scene, from, to, Colors::WHITE);

        Timer timer = scene.GetTimer(id);
        timer.start = scene.GetTime();
        scene.SetTimer(id, timer);
    }
}

void Systems::ShootAtShip(Scene &scene, int id)
{
    float current = scene.GetTime();
    float elapsed = scene.GetTimer(id).Elapsed(current);
    float cooldown = scene.GetAliens().BULLET_COOLDOWN;

    AI ai = scene.GetAI(id);
    Transform transform = scene.GetTransform(id);

    if (elapsed < cooldown)
    {
        return;
    }

    for (auto &ship : scene.GetShips().GetIds())
    {
        Vector3 shipPosition = scene.GetTransform(ship).position;

        if (Utils::Distance(transform.position, shipPosition) < ai.attackRange)
        {
            Vector3 from = transform.position;
            Vector3 to = shipPosition;

            scene.GetBullets().ShootAt(scene, from, to, Colors::RED);

            Timer timer = scene.GetTimer(id);
            timer.start = scene.GetTime();
            scene.SetTimer(id, timer);

            break;
        }
    }
}

void Systems::UpdatePosition(Scene &scene, int id)
{
    Physics physics = scene.GetPhysics(id);
    Transform transform = scene.GetTransform(id);

    float elapsed = scene.GetDeltaTime() / 1000.0f;

    physics.velocity += physics.acceleration * elapsed;
    transform.position += physics.velocity * elapsed;

    // float width = 20.0f;
    // if (transform.position.x > width)
    //{
    //     transform.position.x = -width;
    // }
    // else if (transform.position.x < -width)
    //{
    //     transform.position.x = width;
    // }

    // float height = 20.0f;
    // if (transform.position.y > height)
    //{
    //     transform.position.y = -height;
    // }
    // else if (transform.position.y < -height)
    //{
    //     transform.position.y = height;
    // }

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

void Systems::CheckBulletHit(Scene &scene, int id)
{
    std::vector<int> targets;
    for (auto &ship : scene.GetShips().GetIds())
    {
        targets.push_back(ship);
    }
    for (auto &asteroid : scene.GetAsteroids().GetIds())
    {
        targets.push_back(asteroid);
    }
    for (auto &alien : scene.GetAliens().GetIds())
    {
        targets.push_back(alien);
    }
    for (auto &planet : scene.GetPlanets().GetIds())
    {
        targets.push_back(planet);
    }

    for (auto &target : targets)
    {
        if (Collider::IsHit(scene, id, target))
        {
            Health health;

            health = scene.GetHealth(id);
            health.points--;
            scene.SetHealth(id, health);

            health = scene.GetHealth(target);
            health.points--;
            scene.SetHealth(target, health);

            scene.GetParticles().Ricochet(scene, id);
        }
    }
}

void Systems::ApplyGravity(Scene &scene, int id)
{
    Vector3 position = scene.GetTransform(id).position;

    for (auto &planet : scene.GetPlanets().GetIds())
    {
        AI ai = scene.GetAI(planet);

        Vector3 planetPosition = scene.GetTransform(planet).position;

        if (Utils::Distance(position, planetPosition) < ai.attackRange)
        {
            Physics physics = scene.GetPhysics(id);

            Vector3 to = planetPosition;
            Vector3 from = scene.GetTransform(id).position;
            Vector3 direction = (to - from).Normalize();

            // Bigger planets have more gravity :)
            float scale = scene.GetCollider(planet).radius * 0.5f;
            physics.acceleration += direction * scale;

            scene.SetPhysics(id, physics);
        }
    }
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

void Systems::ChangeColor(Scene &scene, int id)
{
    float current = scene.GetTime();
    float elapsed = scene.GetTimer(id).Elapsed(current);

    if (elapsed < 1.0f)
    {
        return;
    }

    Model model = scene.GetModel(id);
    model.color.SetColor(Colors::RANDOM);
    scene.SetModel(id, model);

    Timer timer = scene.GetTimer(id);
    timer.start = scene.GetTime();
    scene.SetTimer(id, timer);
}

void Systems::SpinPlanet(Scene &scene, int id)
{
    Transform transform = scene.GetTransform(id);

    float deltaRotation = 1.0f / scene.GetCollider(id).radius;

    transform.rotation.x += deltaRotation;
    transform.rotation.y += deltaRotation;

    transform.rotation.x = fmod(transform.rotation.x, 360.0f);
    transform.rotation.y = fmod(transform.rotation.y, 360.0f);

    scene.SetTransform(id, transform);
}

void Systems::CheckCollision(Scene &scene, int id)
{
    std::vector<int> targets;

    if (scene.GetAI(id).attackRange == 0.0f) // Is ship
    {
        for (auto &alien : scene.GetAliens().GetIds())
        {
            targets.push_back(alien);
        }
        for (auto &planet : scene.GetPlanets().GetIds())
        {
            targets.push_back(planet);
        }
    }

    for (auto &target : targets)
    {
        if (Collider::IsHit(scene, id, target))
        {
            Physics physics = scene.GetPhysics(id);
            Transform transform = scene.GetTransform(id);

            float elapsed = scene.GetDeltaTime() / 1000.0f;

            transform.position -= physics.velocity * elapsed;

            Vector3 from = scene.GetTransform(target).position;
            Vector3 to = transform.position;
            Vector3 direction = (to - from).Normalize();
            // physics.velocity += physics.acceleration * elapsed;
            physics.velocity = direction * 10.0f;

            scene.SetPhysics(id, physics);
            scene.SetTransform(id, transform);

            scene.GetParticles().Ricochet(scene, id);
        }
    }
}