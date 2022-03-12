#include "stdafx.h"

#include "Scene.h"

#include "Systems/Systems.h"

Scene::Scene() : m_id(0), m_deltaTime(0.0f)
{
    // Initialize time variables
    m_start = std::chrono::steady_clock::now();
    m_current = m_start;
    m_time = m_current - m_start;

    // Initialize camera position
    // m_position = Vector3(0.0f, 0.0f, 10.0f);
    // m_position = Vector3(0.0f, 0.0f, 30.0f);
    // m_position = Vector3(0.0f, 0.0f, 50.0f);
    m_position = Vector3(0.0f, 0.0f, 100.0f);
}

void Scene::Init()
{
    m_renderer.Init(*this);

    m_planets.Init(*this); // Planets go first

    m_aliens.Init(*this);
    m_asteroids.Init(*this);
    m_bullets.Init(*this);
    m_particles.Init(*this);
    m_ships.Init(*this);
    m_stars.Init(*this);

    // TODO: Initialize space but leave all objects inactive. Use level data to generate objects.
}

void Scene::Shutdown()
{
}

Vector3 Scene::GetMousePosition() const
{
    return m_renderer.GetMousePosition();
}

float Scene::GetDeltaTime() const
{
    return m_deltaTime;
}

float Scene::GetTime() const
{
    return m_time.count();
}

AI Scene::GetAI(int id) const
{
    return m_ai[id];
}

Collider Scene::GetCollider(int id) const
{
    return m_collider[id];
}

Health Scene::GetHealth(int id) const
{
    return m_health[id];
}

Model Scene::GetModel(int id) const
{
    return m_model[id];
}

Physics Scene::GetPhysics(int id) const
{
    return m_physics[id];
}

Timer Scene::GetTimer(int id) const
{
    return m_timer[id];
}

Transform Scene::GetTransform(int id) const
{
    return m_transform[id];
}

Aliens &Scene::GetAliens()
{
    return m_aliens;
}

Asteroids &Scene::GetAsteroids()
{
    return m_asteroids;
}

Bullets &Scene::GetBullets()
{
    return m_bullets;
}

Particles &Scene::GetParticles()
{
    return m_particles;
}

Planets &Scene::GetPlanets()
{
    return m_planets;
}

Ships &Scene::GetShips()
{
    return m_ships;
}

Stars &Scene::GetStars()
{
    return m_stars;
}

std::vector<int> Scene::GetAllIds() const
{
    std::vector<int> ids;
    for (auto &id : m_aliens.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_asteroids.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_bullets.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_particles.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_planets.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_ships.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_stars.GetIds())
    {
        ids.push_back(id);
    }
    return ids;
}

void Scene::SetAI(int id, AI ai)
{
    m_ai[id] = ai;
}

void Scene::SetCollider(int id, Collider collider)
{
    m_collider[id] = collider;
}

void Scene::SetHealth(int id, Health health)
{
    m_health[id] = health;
}

void Scene::SetModel(int id, Model model)
{
    m_model[id] = model;
}

void Scene::SetPhysics(int id, Physics physics)
{
    m_physics[id] = physics;
}

void Scene::SetTimer(int id, Timer timer)
{
    m_timer[id] = timer;
}

void Scene::SetTransform(int id, Transform transform)
{
    m_transform[id] = transform;
}

int Scene::CreateId()
{
    m_ai.push_back(AI());
    m_collider.push_back(Collider());
    m_health.push_back(Health());
    m_model.push_back(Model());
    m_physics.push_back(Physics());
    m_timer.push_back(Timer());
    m_transform.push_back(Transform());

    m_id++;
    return m_id - 1; // Array index starts at 0
}

void Scene::Update(float deltaTime)
{
    SetTime(deltaTime);
    MoveCamera(deltaTime);

    for (auto &id : m_ships.GetIds())
    {
        m_systems.RotateTowardsMouse(*this, id);
        m_systems.AccelerateShip(*this, id);
        m_systems.ApplyGravity(*this, id);
        m_systems.LimitShipVelocity(*this, id);
        m_systems.ShootAtMouse(*this, id);
        m_systems.UpdatePosition(*this, id);
        m_systems.CheckShipCollision(*this, id);
    }

    for (auto &id : m_aliens.GetIds())
    {
        m_systems.RotateTowardsShip(*this, id);
        m_systems.ShootAtShip(*this, id);
    }

    for (auto &id : m_asteroids.GetIds())
    {
        m_systems.UpdatePosition(*this, id);
        m_systems.AddRotation(*this, id);
        m_systems.RotateTowardsShip(*this, id);
    }

    for (auto &id : m_bullets.GetIds())
    {
        m_systems.UpdatePosition(*this, id);
        m_systems.AddRotation(*this, id);
        m_systems.CheckBulletHit(*this, id);
    }

    for (auto &id : m_particles.GetIds())
    {
        m_systems.UpdatePosition(*this, id);
        m_systems.AddRotation(*this, id);
    }

    for (auto &id : m_planets.GetIds())
    {
        m_systems.SpinPlanet(*this, id);
    }

    for (auto &id : m_stars.GetIds())
    {
        // Disco mode
        // m_systems.ChangeColor(*this, id);
    }

    UpdatePools();

    m_renderer.Update(deltaTime);
}

void Scene::Render()
{
    m_renderer.Render();
}

void Scene::SetTime(float deltaTime)
{
    m_deltaTime = deltaTime;
    m_current = std::chrono::steady_clock::now();
    m_time = m_current - m_start;
}

void Scene::MoveCamera(float deltaTime)
{
    float deltaVelocity = deltaTime / 10.0f;

    if (App::IsKeyPressed(VK_NUMPAD6))
    {
        m_position.x += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD4))
    {
        m_position.x -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD8))
    {
        m_position.z -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD2))
    {
        m_position.z += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD7))
    {
        m_position.y += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD9))
    {
        m_position.y -= deltaVelocity;
    }

    // Follow ship with camera
    if (!m_ships.GetIds().empty())
    {
        int id = m_ships.GetIds().front();
        Vector3 from = GetTransform(id).position;
        Vector3 to = GetMousePosition();
        Vector3 direction = to - from;
        if (direction != Vector3())
        {
            direction = direction.Normalize();
        }

        // Put the camera behind the ship
        m_renderer.SetCameraPosition(from + m_position - direction * 10.0f);
        // Look in front of the ship
        m_renderer.SetCameraTarget(from + direction * 2.0f);
    }
}

void Scene::UpdatePools()
{
    m_aliens.Update(*this);
    m_asteroids.Update(*this);
    m_bullets.Update(*this);
    m_particles.Update(*this);
    m_planets.Update(*this);
    m_ships.Update(*this);
    m_stars.Update(*this);
}