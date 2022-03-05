#pragma once

#include "Components/Mesh/Mesh.h"
#include "Components/Physics/Physics.h"
#include "Components/Transform/Transform.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Rect/Rect.h"
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
    // Unique ID
    static const int MAX_OBJECTS = 1000;
    int m_id;

    // 3D graphics
    Rect m_viewport;
    Camera m_camera;
    Matrix m_world;
    Matrix m_view;
    Matrix m_projection;
    std::vector<Triangle> m_triangles;

    // Component arrays
    Mesh *m_mesh;
    Physics *m_physics;
    Transform *m_transform;

    // Object pools
    Asteroids m_asteroids;
    Grid m_grid;
    Ships m_ships;

    // Helper functions
    void SetViewport();
    void SetCamera();
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();

    void HandleInput();
    void UpdateTriangles();
    void RenderTriangles();
    void RenderBorder();
};