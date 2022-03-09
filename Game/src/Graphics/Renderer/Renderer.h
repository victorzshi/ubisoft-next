#pragma once

#include "Graphics/Camera/Camera.h"
#include "Graphics/Face/Face.h"
#include "Math/Matrix/Matrix.h"

class Scene;

class Renderer
{
  public:
    Camera m_camera;

    Renderer();

    void Init(Scene &scene);

    Vector3 GetMousePosition() const;

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

    Scene *m_scene;

    // 3D graphics
    Matrix m_world;
    Matrix m_view;
    Matrix m_viewInverse;
    Matrix m_projection;
    Vector3 m_mouse;
    std::vector<Face> m_visible;

    // Helper functions
    void SetCamera();
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();
    void SetMousePosition();

    void MoveCamera(float deltaTime);
    void UpdateVisible();
    void SortVisible();
    void RenderVisible();
    void RenderBorder();
};