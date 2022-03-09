#include "stdafx.h"

#include "Scene.h"

#include "Systems/Systems.h"

Scene::Scene() : m_id(0), m_deltaTime(0.0f)
{
    m_start = std::chrono::steady_clock::now();
    m_current = m_start;
    m_time = m_current - m_start;
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

    for (int id = m_ships.GetBegin(); id < m_ships.GetSize(); id++)
    {
        Systems::MoveShip(*this, id);
        Systems::ShootBullet(*this, id);
        Systems::UpdatePosition(*this, id);
    }

    for (int id = m_asteroids.GetBegin(); id < m_asteroids.GetSize(); id++)
    {
        Systems::UpdatePosition(*this, id);
        Systems::AddRotation(*this, id);
    }

    for (int id = m_bullets.GetBegin(); id < m_bullets.GetSize(); id++)
    {
        Systems::UpdatePosition(*this, id);
        Systems::AddRotation(*this, id);
        Systems::CheckBulletHit(*this, id);
    }

    // Follow ship with camera
    int id = m_ships.GetBegin();
    Transform transform = GetTransform(id);
    //m_renderer.m_camera.from = transform.position + Vector3(0.0f, 5.0f, 10.0f);
    m_renderer.m_camera.to = transform.position;

    m_renderer.Update(deltaTime);
}

void Scene::Render()
{
    m_renderer.Render();
#ifdef _DEBUG
    App::Print(10.0f, 100.0f, std::to_string(m_time.count()).c_str(), 0.0f, 1.0f, 0.0f);
#endif
}

void Scene::SetTime(float deltaTime)
{
    m_deltaTime = deltaTime;
    m_current = std::chrono::steady_clock::now();
    m_time = m_current - m_start;
}

std::vector<int> Scene::GetActiveIds() const
{
    std::vector<int> ids;
    for (int id = m_asteroids.GetBegin(); id < m_asteroids.GetSize(); id++)
    {
        ids.push_back(id);
    }
    for (int id = m_bullets.GetBegin(); id < m_bullets.GetSize(); id++)
    {
        ids.push_back(id);
    }
    for (int id = m_grid.GetBegin(); id < m_grid.GetSize(); id++)
    {
        ids.push_back(id);
    }
    for (int id = m_ships.GetBegin(); id < m_ships.GetSize(); id++)
    {
        ids.push_back(id);
    }
    return ids;
}