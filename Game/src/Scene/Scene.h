#pragma once

#include <chrono>

#include "Components/Model/Model.h"
#include "Components/Physics/Physics.h"
#include "Components/Timer/Timer.h"
#include "Components/Transform/Transform.h"
#include "Graphics/Renderer/Renderer.h"
#include "Pools/Asteroids/Asteroids.h"
#include "Pools/Bullets/Bullets.h"
#include "Pools/Grid/Grid.h"
#include "Pools/Ships/Ships.h"

class Scene
{
  public:
    Scene();

    void Init();
    void Shutdown();

    // Utilities
    Vector3 GetMousePosition() const;
    float GetDeltaTime() const;
    float GetTime() const;

    // Get component arrays
    Model GetModel(int id) const;
    Physics GetPhysics(int id) const;
    Timer GetTimer(int id) const;
    Transform GetTransform(int id) const;

    // Get object pools
    Asteroids &GetAsteroids();
    Bullets &GetBullets();
    Grid &GetGrid();
    Ships &GetShips();

    // Get IDs of active objects
    std::vector<int> GetActiveIds() const;

    // Set component arrays
    void SetModel(int id, Model model);
    void SetPhysics(int id, Physics physics);
    void SetTimer(int id, Timer timer);
    void SetTransform(int id, Transform transform);

    // Create new object with unique ID
    int CreateId();

    void Update(float deltaTime);
    void Render();

  private:
    // Unique ID
    int m_id;

    // Track time
    float m_deltaTime;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_current;
    std::chrono::duration<float> m_time;

    // Component arrays
    std::vector<Model> m_model;
    std::vector<Physics> m_physics;
    std::vector<Timer> m_timer;
    std::vector<Transform> m_transform;

    // Object pools
    Asteroids m_asteroids;
    Bullets m_bullets;
    Grid m_grid;
    Ships m_ships;

    // Handle graphics
    Renderer m_renderer;

    // Helper functions
    void SetTime(float deltaTime);
};