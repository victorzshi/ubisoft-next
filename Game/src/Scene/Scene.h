#pragma once

#include "Components/Mesh/Mesh.h"
#include "Components/Physics/Physics.h"
#include "Components/Transform/Transform.h"
#include "Graphics/Camera/Camera.h"
#include "Math/Matrix/Matrix.h"
#include "Pools/Asteroids/Asteroids.h"
#include "Pools/Grid/Grid.h"
#include "Pools/Ships/Ships.h"

class Scene
{
  public:
    Scene();

    void Init();
    void Shutdown();

    Mesh GetMesh(int id) const;
    Physics GetPhysics(int id) const;
    Transform GetTransform(int id) const;

    void SetMesh(int id, Mesh mesh);
    void SetPhysics(int id, Physics physics);
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

    // 3D graphics
    Camera m_camera;
    Matrix m_world;
    Matrix m_view;
    Matrix m_viewInverse;
    Matrix m_projection;
    Vector3 m_click;
    std::vector<Face> m_visible;

    // Component arrays
    std::vector<Mesh> m_mesh;
    std::vector<Physics> m_physics;
    std::vector<Transform> m_transform;

    // Object pools
    Asteroids m_asteroids;
    Grid m_grid;
    Ships m_ships;

    // Helper functions
    void SetCamera();
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();
    void SetClickPosition();

    void MoveCamera(float deltaTime);
    void UpdateVisible();
    void RenderVisible();
    void RenderBorder();
};