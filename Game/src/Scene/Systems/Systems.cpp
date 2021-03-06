#include "stdafx.h"

#include "Systems.h"

#include "Scene/Scene.h"

#include "Math/Utils/Utils.h"

void Systems::MoveCamera(Scene &scene, int id)
{
    float closest = Utils::MaxFloat();
    for (auto &planet : scene.GetPlanets().GetIds())
    {
        Vector3 shipPosition = scene.GetTransform(id).position;
        Vector3 planetPosition = scene.GetTransform(planet).position;

        float distance = Utils::Distance(shipPosition, planetPosition) - scene.GetCollider(planet).radius;
        if (distance < closest)
        {
            closest = distance;
        }
    }

    // Switch between zoomed in and zoomed out views
    Vector3 position = scene.GetScenePosition();
    if (closest < 20.0f)
    {
        position.z = Utils::Lerp(position.z, 20.0f, 0.05f);
    }
    else
    {
        position.z = Utils::Lerp(position.z, 200.0f, 0.01f);
    }
    scene.SetScenePosition(position);

    // Follow ship with camera
    Vector3 from = scene.GetTransform(id).position;
    Vector3 to = scene.GetMousePosition();
    Vector3 direction = (to - from).Normalize();

    // Put the camera behind the ship
    scene.SetCameraPosition(from + position + direction * -4.0f);
    // Aim in front of the ship
    scene.SetCameraTarget(from + direction);
}

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
    }

    scene.SetTransform(id, transform);
}

void Systems::AccelerateShip(Scene &scene, int id)
{
    float deltaAcceleration = scene.GetShips().DELTA_ACCELERATION;

    Vector3 direction;
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        direction.x = +deltaAcceleration;
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        direction.x = -deltaAcceleration;
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        direction.y = +deltaAcceleration;
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        direction.y = -deltaAcceleration;
    }

    if (direction == Vector3())
    {
        return;
    }

    Timer timer = scene.GetTimer(id);
    Physics physics = scene.GetPhysics(id);
    Transform transform = scene.GetTransform(id);

    Vector3 from = direction.Normalize();
    Vector3 to = (scene.GetMousePosition() - transform.position).Normalize();

    if (from.Dot(to) > 0.8f)
    {
        timer.stayAlive -= scene.GetDeltaTime() / 500.0f;
        physics.acceleration = direction * 2.0f;
        scene.GetShips().SetMaxVelocity(10.0f);
        scene.GetParticles().Boost(scene, id, to);
    }
    else
    {
        timer.stayAlive -= scene.GetDeltaTime() / 1000.0f;
        physics.acceleration = direction;
        scene.GetShips().SetMaxVelocity(5.0f);
    }

    scene.SetTimer(id, timer);
    scene.SetPhysics(id, physics);
}

void Systems::ShootAtMouse(Scene &scene, int id)
{
    if (!App::IsKeyPressed(VK_LBUTTON))
    {
        return;
    }

    float current = scene.GetTime();

    Timer timer = scene.GetTimer(id);

    if (timer.Elapsed(current) > timer.cooldown && timer.ammo > 0)
    {
        Vector3 from = scene.GetTransform(id).position;
        Vector3 to = scene.GetMousePosition();

        scene.GetBullets().ShipShootAt(scene, from, to);

        Timer timer = scene.GetTimer(id);
        timer.start = scene.GetTime();
        timer.ammo -= scene.GetDeltaTime() / 50.0f;
        scene.SetTimer(id, timer);
    }
}

void Systems::AttackShip(Scene &scene, int id)
{
    float current = scene.GetTime();

    AI ai = scene.GetAI(id);
    Timer timer = scene.GetTimer(id);
    Transform transform = scene.GetTransform(id);

    if (ai.isBomber)
    {
        Physics physics = scene.GetPhysics(id);

        for (auto &ship : scene.GetShips().GetIds())
        {
            Vector3 shipPosition = scene.GetTransform(ship).position;

            if (Utils::Distance(transform.position, shipPosition) < ai.attackRange)
            {
                Vector3 from = transform.position;
                Vector3 to = shipPosition;
                Vector3 direction = (to - from).Normalize();

                physics.acceleration = direction * 10.0f;
                physics.velocity = direction * 5.0f;

                scene.SetPhysics(id, physics);

                Timer timer = scene.GetTimer(id);
                if (timer.stayAlive == 0.0f)
                {
                    timer.start = scene.GetTime();
                    timer.stayAlive = 10.0f;
                    scene.SetTimer(id, timer);
                }

                scene.GetParticles().Boost(scene, id, direction);

                break;
            }
        }
    }
    else
    {
        if (timer.Elapsed(current) < timer.cooldown)
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

                scene.GetBullets().AlienShootAt(scene, from, to);

                Timer timer = scene.GetTimer(id);
                timer.start = scene.GetTime();
                scene.SetTimer(id, timer);

                break;
            }
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

    scene.SetPhysics(id, physics);
    scene.SetTransform(id, transform);
}

void Systems::AddRotationFromVelocity(Scene &scene, int id)
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

void Systems::AddRotationFromConstant(Scene &scene, int id)
{
    Physics physics = scene.GetPhysics(id);
    Transform transform = scene.GetTransform(id);

    float deltaRotation = scene.GetDeltaTime() / 10.0f;

    transform.rotation.x += deltaRotation;
    transform.rotation.y += deltaRotation * 0.5f;

    transform.rotation.x = fmod(transform.rotation.x, 360.0f);
    transform.rotation.y = fmod(transform.rotation.y, 360.0f);
    transform.rotation.z = fmod(transform.rotation.z, 360.0f);

    scene.SetTransform(id, transform);
}

void Systems::CheckBulletHit(Scene &scene, int id)
{
    std::vector<int> targets;

    // XXX: No friendly fire :)
    Model model = scene.GetModel(id);
    int r = model.color.r;
    int g = model.color.g;
    int b = model.color.b;
    bool isShip = r == 255 && g == 255 && b == 255 ? true : false;
    if (isShip)
    {
        for (auto &alien : scene.GetAliens().GetIds())
        {
            targets.push_back(alien);
        }
    }
    else
    {
        for (auto &ship : scene.GetShips().GetIds())
        {
            targets.push_back(ship);
        }
    }

    // All bullets collide with planets
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
            health.points--; // Bullets have 1 health
            scene.SetHealth(id, health);

            health = scene.GetHealth(target);
            health.points -= 5;
            scene.SetHealth(target, health);

            if (scene.GetAI(target).attackRange == 0.0f)
            {
                scene.GetUI()->scoring.damageTaken += 5;
            }

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

    float max = scene.GetShips().GetMaxVelocity();
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

void Systems::CheckPlanetCollision(Scene &scene, int id)
{
    for (auto &planet : scene.GetPlanets().GetIds())
    {
        AI ai = scene.GetAI(id);

        if (ai.attackRange > 0.0f && !ai.isBomber) // Is a stationary turret.
        {
            return;
        }

        if (Collider::IsHit(scene, id, planet))
        {
            Physics physics = scene.GetPhysics(id);
            Transform transform = scene.GetTransform(id);

            float elapsed = scene.GetDeltaTime() / 1000.0f;

            transform.position -= physics.velocity * elapsed;

            Vector3 from = scene.GetTransform(planet).position;
            Vector3 to = transform.position;
            Vector3 direction = (to - from).Normalize();
            physics.velocity = direction * 5.0f;
            physics.acceleration = Vector3();

            scene.SetPhysics(id, physics);
            scene.SetTransform(id, transform);

            Health health;

            health = scene.GetHealth(id);
            health.points -= 5;
            scene.SetHealth(id, health);

            // XXX: Update ship score.
            if (ai.attackRange == 0.0f)
            {
                scene.GetUI()->scoring.damageTaken += 5;
            }

            scene.GetParticles().Ricochet(scene, id);
        }
    }
}

void Systems::CheckAlienCollision(Scene &scene, int id)
{
    for (auto &alien : scene.GetAliens().GetIds())
    {
        if (Collider::IsHit(scene, id, alien))
        {
            bool isBomber = scene.GetAI(alien).isBomber;

            Physics physics = scene.GetPhysics(id);
            Transform transform = scene.GetTransform(id);

            float elapsed = scene.GetDeltaTime() / 1000.0f;

            transform.position -= physics.velocity * elapsed;

            Vector3 from = scene.GetTransform(alien).position;
            Vector3 to = transform.position;
            Vector3 direction = (to - from).Normalize();
            if (isBomber)
            {
                physics.velocity = direction * 20.0f;
            }
            else
            {
                physics.velocity = direction * 10.0f;
            }
            physics.acceleration = Vector3();

            scene.SetPhysics(id, physics);
            scene.SetTransform(id, transform);

            Health health;

            health = scene.GetHealth(id);
            if (isBomber)
            {
                health.points -= 20;
                scene.GetUI()->scoring.damageTaken += 20;
            }
            else
            {
                health.points -= 10;
                scene.GetUI()->scoring.damageTaken += 10;
            }
            scene.SetHealth(id, health);

            health = scene.GetHealth(alien);
            health.points -= 10;
            scene.SetHealth(alien, health);

            scene.GetParticles().Ricochet(scene, id);
        }
    }
}

void Systems::PickUpFuel(Scene &scene, int id)
{
    for (auto &fuel : scene.GetFuel().GetIds())
    {
        if (Collider::IsHit(scene, id, fuel))
        {
            Health health;

            health = scene.GetHealth(id);
            health.points = 100; // Reset health
            scene.SetHealth(id, health);

            // Destroy fuel block
            health = scene.GetHealth(fuel);
            health.points = 0;
            scene.SetHealth(fuel, health);

            Timer timer = scene.GetTimer(id);
            timer.stayAlive = 100.0f;
            timer.ammo = 100.0f;
            scene.SetTimer(id, timer);
        }
    }
}

void Systems::ScaleSmaller(Scene &scene, int id)
{
    Transform transform = scene.GetTransform(id);

    transform.scaling.x = Utils::Lerp(transform.scaling.x, 0.0f, 0.02f);
    transform.scaling.y = Utils::Lerp(transform.scaling.y, 0.0f, 0.02f);
    transform.scaling.z = Utils::Lerp(transform.scaling.z, 0.0f, 0.02f);

    scene.SetTransform(id, transform);
}