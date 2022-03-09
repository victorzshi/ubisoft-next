#pragma once

#include <chrono>

#include "Components/Model/Model.h"
#include "Components/Physics/Physics.h"
#include "Components/Timer/Timer.h"
#include "Components/Transform/Transform.h"
#include "Graphics/Camera/Camera.h"
#include "Math/Matrix/Matrix.h"
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

    Vector3 GetMousePosition() const;
    float GetDeltaTime() const;
    float GetTime() const;
    Model GetModel(int id) const;
    Physics GetPhysics(int id) const;
    Timer GetTimer(int id) const;
    Transform GetTransform(int id) const;
    Asteroids &GetAsteroids();
    Bullets &GetBullets();
    Grid &GetGrid();
    Ships &GetShips();

    void SetModel(int id, Model model);
    void SetPhysics(int id, Physics physics);
    void SetTimer(int id, Timer timer);
    void SetTransform(int id, Transform transform);

    int CreateId();

    void Update(float deltaTime);
    void Render();

  private:
    // Constants for viewing frustum
    const float m_SCREEN_WIDTH = 960.0f;
    const float m_SCREEN_HEIGHT = 540.0f;
    const float m_FOV = 90.0f;
    const float m_THETA = m_FOV * (PI / 180.0f);
    const float m_DISTANCE = 1.0f / tanf(m_THETA * 0.5f);
    const float m_ASPECT_RATIO = m_SCREEN_WIDTH / m_SCREEN_HEIGHT;
    const float m_Z_NEAR = 0.1f;
    const float m_Z_FAR = 25.0f;

    // Unique ID
    int m_id;

    // Track time
    float m_deltaTime;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_current;
    std::chrono::duration<float> m_time;

    // 3D graphics
    Camera m_camera;
    Matrix m_world;
    Matrix m_view;
    Matrix m_viewInverse;
    Matrix m_projection;
    Vector3 m_mouse;
    std::vector<Face> m_visible;

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
    std::vector<int> m_inactive;

    // Helper functions
    void SetCamera();
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();
    void SetMousePosition();
    void SetTime(float deltaTime);

    std::vector<int> GetAllActiveIds() const;

    void MoveCamera(float deltaTime);
    void UpdateVisible();
    void SortVisible();
    void RenderVisible();
    void RenderBorder();
};