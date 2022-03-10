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
    m_position = Vector3(0.0f, 5.0f, 15.0f);
}

void Scene::Init()
{
    m_renderer.Init(*this);
    m_asteroids.Init(*this);
    m_bullets.Init(*this);
    m_grid.Init(*this);
    m_ships.Init(*this);
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

Asteroids &Scene::GetAsteroids()
{
    return m_asteroids;
}

Bullets &Scene::GetBullets()
{
    return m_bullets;
}

Grid &Scene::GetGrid()
{
    return m_grid;
}

Ships &Scene::GetShips()
{
    return m_ships;
}

std::vector<int> Scene::GetAllIds() const
{
    std::vector<int> ids;
    for (auto id : m_asteroids.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_bullets.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_grid.GetIds())
    {
        ids.push_back(id);
    }
    for (auto &id : m_ships.GetIds())
    {
        ids.push_back(id);
    }
    return ids;
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

    for (auto id : m_ships.GetIds())
    {
        Systems::MoveShip(*this, id);
        Systems::ShootBullet(*this, id);
        Systems::UpdatePosition(*this, id);
        Systems::AddRotation(*this, id);
    }

    for (auto id : m_asteroids.GetIds())
    {
        Systems::UpdatePosition(*this, id);
        Systems::AddRotation(*this, id);
    }

    for (auto id : m_bullets.GetIds())
    {
        Systems::UpdatePosition(*this, id);
        Systems::AddRotation(*this, id);
    }

    // TODO: Move this into Game.cpp
    m_renderer.Update(deltaTime);
    m_asteroids.UpdateIds(*this);
    m_bullets.UpdateIds(*this);
    m_grid.UpdateIds(*this);
    m_ships.UpdateIds(*this);
}

void Scene::Render()
{
    // TODO: Move this into Game.cpp
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
    float deltaVelocity = deltaTime / 100.0f;

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
    int id = m_ships.GetIds().front();
    Vector3 ship = GetTransform(id).position;
    Vector3 mouse = GetMousePosition();
    Vector3 direction = mouse - ship;
    if (direction != Vector3())
    {
        direction = direction.Normalize() * 2.0f;
    }

    m_renderer.SetCameraPosition(ship + m_position);
    m_renderer.SetCameraTarget(ship + direction);
}