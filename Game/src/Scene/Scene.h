#pragma once

#include <chrono>

#include "Components/AI/AI.h"
#include "Components/Collider/Collider.h"
#include "Components/Health/Health.h"
#include "Components/Model/Model.h"
#include "Components/Physics/Physics.h"
#include "Components/Timer/Timer.h"
#include "Components/Transform/Transform.h"
#include "Graphics/Renderer/Renderer.h"
#include "Pools/Aliens/Aliens.h"
#include "Pools/Bullets/Bullets.h"
#include "Pools/Fuel/Fuel.h"
#include "Pools/Particles/Particles.h"
#include "Pools/Planets/Planets.h"
#include "Pools/Ships/Ships.h"
#include "Pools/Stars/Stars.h"
#include "Scene/Systems/Systems.h"

class Scene
{
  public:
    Scene();

    void Init(Renderer &renderer);

    // Utilities
    Vector3 GetScenePosition() const;
    Vector3 GetMousePosition() const;
    float GetDeltaTime() const;
    float GetTime() const;
    void SetPause(std::chrono::time_point<std::chrono::steady_clock> pause);

    // Get component arrays
    AI GetAI(int id) const;
    Collider GetCollider(int id) const;
    Health GetHealth(int id) const;
    Model GetModel(int id) const;
    Physics GetPhysics(int id) const;
    Timer GetTimer(int id) const;
    Transform GetTransform(int id) const;

    // Get object pools
    Aliens &GetAliens();
    Bullets &GetBullets();
    Fuel &GetFuel();
    Particles &GetParticles();
    Planets &GetPlanets();
    Ships &GetShips();
    Stars &GetStars();

    // Get IDs of all active objects
    std::vector<int> GetAllIds() const;

    // Set camera related
    void SetScenePosition(Vector3 position);
    void SetCameraPosition(Vector3 position);
    void SetCameraTarget(Vector3 target);

    // Set component arrays
    void SetAI(int id, AI ai);
    void SetCollider(int id, Collider collider);
    void SetHealth(int id, Health health);
    void SetModel(int id, Model model);
    void SetPhysics(int id, Physics physics);
    void SetTimer(int id, Timer timer);
    void SetTransform(int id, Transform transform);

    // Create new object with unique ID
    int CreateId();

    void Update(float deltaTime);

  private:
    // Handle camera
    Renderer *m_renderer;
    Vector3 m_position;

    // Unique ID
    int m_id;

    // Track time
    float m_deltaTime;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_current;
    std::chrono::duration<float> m_time;

    // Component arrays
    std::vector<AI> m_ai;
    std::vector<Collider> m_collider;
    std::vector<Health> m_health;
    std::vector<Model> m_model;
    std::vector<Physics> m_physics;
    std::vector<Timer> m_timer;
    std::vector<Transform> m_transform;

    // Object pools
    Aliens m_aliens;
    Bullets m_bullets;
    Fuel m_fuel;
    Particles m_particles;
    Planets m_planets;
    Ships m_ships;
    Stars m_stars;

    // Gameplay logic
    Systems m_systems;

    // Helper functions
    void SetTime(float deltaTime);
    void UpdatePools();
};