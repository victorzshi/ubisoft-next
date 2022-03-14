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
    m_position = Vector3(0.0f, 0.0f, 300.0f);
}

void Scene::Init()
{
    m_renderer.Init(*this);

    // Planets go first
    m_planets.Init(*this);
    // Because aliens and fuel depend on planet position
    m_aliens.Init(*this);
    m_fuel.Init(*this);

    m_bullets.Init(*this);
    m_particles.Init(*this);
    m_ships.Init(*this);
    m_stars.Init(*this);

    // TODO: Initialize space but leave all objects inactive. Use level data to generate objects.
}

void Scene::Shutdown()
{
}

void Scene::SetPause(std::chrono::time_point<std::chrono::steady_clock> pause)
{
    m_start += std::chrono::steady_clock::now() - pause;
}

Renderer &Scene::GetRenderer()
{
    return m_renderer;
}

Vector3 Scene::GetScenePosition() const
{
    return m_position;
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

Bullets &Scene::GetBullets()
{
    return m_bullets;
}

Fuel &Scene::GetFuel()
{
    return m_fuel;
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
    for (auto &id : m_bullets.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_fuel.GetIds())
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

void Scene::SetScenePosition(Vector3 position)
{
    m_position = position;
}

void Scene::SetCameraPosition(Vector3 position)
{
    m_renderer.SetCameraPosition(position);
}

void Scene::SetCameraTarget(Vector3 target)
{
    m_renderer.SetCameraTarget(target);
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

    for (auto &id : m_ships.GetIds())
    {
        m_systems.MoveCamera(*this, id);
        m_systems.RotateTowardsMouse(*this, id);
        m_systems.AccelerateShip(*this, id);
        m_systems.ApplyGravity(*this, id);
        m_systems.LimitShipVelocity(*this, id);
        m_systems.ShootAtMouse(*this, id);
        m_systems.UpdatePosition(*this, id);
        m_systems.CheckPlanetCollision(*this, id);
        m_systems.CheckAlienCollision(*this, id);
        m_systems.PickUpFuel(*this, id);
    }

    for (auto &id : m_aliens.GetIds())
    {
        m_systems.AddRotationFromConstant(*this, id);
        m_systems.RotateTowardsShip(*this, id);
        m_systems.AttackShip(*this, id);
        m_systems.UpdatePosition(*this, id);
        m_systems.CheckPlanetCollision(*this, id);
    }

    for (auto &id : m_bullets.GetIds())
    {
        m_systems.AddRotationFromVelocity(*this, id);
        m_systems.UpdatePosition(*this, id);
        m_systems.CheckBulletHit(*this, id);
    }

    for (auto &id : m_particles.GetIds())
    {
        m_systems.ScaleSmaller(*this, id);
        m_systems.AddRotationFromVelocity(*this, id);
        m_systems.UpdatePosition(*this, id);
    }

    for (auto &id : m_planets.GetIds())
    {
        m_systems.SpinPlanet(*this, id);
    }

    for (auto &id : m_stars.GetIds())
    {
#ifdef _DEBUG
        m_systems.ChangeColor(*this, id);
#endif
    }

    for (auto &id : m_fuel.GetIds())
    {
        m_systems.AddRotationFromConstant(*this, id);
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

void Scene::UpdatePools()
{
    m_aliens.Update(*this);
    m_bullets.Update(*this);
    m_fuel.Update(*this);
    m_particles.Update(*this);
    m_planets.Update(*this);
    m_ships.Update(*this);
    m_stars.Update(*this);
}