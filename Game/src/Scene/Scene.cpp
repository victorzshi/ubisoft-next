#include "stdafx.h"

#include "Scene.h"

#include <algorithm>

#include "Systems/Systems.h"

Scene::Scene() : m_id(0), m_deltaTime(0.0f)
{
    m_start = std::chrono::steady_clock::now();
    m_current = m_start;
    m_time = m_current - m_start;
}

void Scene::Init()
{
    SetCamera();
    SetWorldMatrix();
    SetViewMatrix();
    SetProjectionMatrix();

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
    return m_mouse;
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
#ifdef _DEBUG
    MoveCamera(deltaTime);
#endif
    SetMousePosition();
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
    }

    for (int id = m_bullets.GetBegin(); id < m_bullets.GetSize(); id++)
    {
        Systems::CheckBulletHit(*this, id);
    }

    // Follow ship with camera
    int id = m_ships.GetBegin();
    Transform transform = GetTransform(id);
    m_camera.from = transform.position + Vector3(0.0f, 5.0f, 10.0f);
    m_camera.to = transform.position;

    SetViewMatrix();
    UpdateVisible();
    SortVisible();
}

void Scene::Render()
{
    RenderVisible();
#ifdef _DEBUG
    RenderBorder();
    App::Print(10.0f, 100.0f, std::to_string(m_time.count()).c_str(), 0.0f, 1.0f, 0.0f);
#endif
}

void Scene::SetCamera()
{
    m_camera.from = Vector3(0.0f, 0.0f, 20.0f);
    m_camera.to = Vector3(0.0f, 0.0f, 1.0f);
    m_camera.up = Vector3(0.0f, 1.0f, 0.0f);
}

void Scene::SetWorldMatrix()
{
    Matrix scale = Matrix::Scale(Vector3(1.0f, 1.0f, 1.0f));
    Matrix rotate = Matrix::Identity();
    Matrix translate = Matrix::Translate(Vector3(0.0f, 0.0f, 0.0f));
    m_world = scale * rotate * translate;
}

void Scene::SetViewMatrix()
{
    Vector3 from = m_camera.from;
    Vector3 to = m_camera.to;
    Vector3 up = m_camera.up;

    Vector3 zAxis = (to - from).Normalize();        // Forward
    Vector3 xAxis = zAxis.Cross(up).Normalize();    // Right
    Vector3 yAxis = xAxis.Cross(zAxis).Normalize(); // Up

    zAxis *= -1;

    m_view(0, 0) = xAxis.x;
    m_view(0, 1) = yAxis.x;
    m_view(0, 2) = zAxis.x;
    m_view(0, 3) = 0.0f;
    m_view(1, 0) = xAxis.y;
    m_view(1, 1) = yAxis.y;
    m_view(1, 2) = zAxis.y;
    m_view(1, 3) = 0.0f;
    m_view(2, 0) = xAxis.z;
    m_view(2, 1) = yAxis.z;
    m_view(2, 2) = zAxis.z;
    m_view(2, 3) = 0.0f;
    m_view(3, 0) = -xAxis.Dot(from);
    m_view(3, 1) = -yAxis.Dot(from);
    m_view(3, 2) = -zAxis.Dot(from);
    m_view(3, 3) = 1.0f;

    m_viewInverse(0, 0) = xAxis.x;
    m_viewInverse(0, 1) = xAxis.y;
    m_viewInverse(0, 2) = xAxis.z;
    m_viewInverse(0, 3) = 0.0f;
    m_viewInverse(1, 0) = yAxis.x;
    m_viewInverse(1, 1) = yAxis.y;
    m_viewInverse(1, 2) = yAxis.z;
    m_viewInverse(1, 3) = 0.0f;
    m_viewInverse(2, 0) = zAxis.x;
    m_viewInverse(2, 1) = zAxis.y;
    m_viewInverse(2, 2) = zAxis.z;
    m_viewInverse(2, 3) = 0.0f;
    m_viewInverse(3, 0) = from.x;
    m_viewInverse(3, 1) = from.y;
    m_viewInverse(3, 2) = from.z;
    m_viewInverse(3, 3) = 1.0f;
}

void Scene::SetProjectionMatrix()
{
    float reciprocal = 1.0f / (m_Z_NEAR - m_Z_FAR);

    m_projection(0, 0) = m_DISTANCE / m_ASPECT_RATIO;
    m_projection(1, 1) = m_DISTANCE;
    m_projection(2, 2) = (m_Z_NEAR + m_Z_FAR) * reciprocal;
    m_projection(2, 3) = 2.0f * m_Z_NEAR * m_Z_FAR * reciprocal;
    m_projection(3, 2) = -1.0f;
    m_projection(3, 3) = 0.0f;
}

void Scene::SetMousePosition()
{
    float mouseX, mouseY;
    App::GetMousePos(mouseX, mouseY);

    Vector3 viewPoint;
    viewPoint.x = 2.0f * m_ASPECT_RATIO * mouseX / m_SCREEN_WIDTH - m_ASPECT_RATIO;
    viewPoint.y = -2.0f * mouseY / m_SCREEN_HEIGHT + 1.0f;
    viewPoint.z = -m_DISTANCE;

    Vector3 worldPoint = m_viewInverse * viewPoint;

    if (worldPoint.w != 0.0f)
    {
        worldPoint /= worldPoint.w;
    }

    Vector3 ray = worldPoint - m_camera.from;

    // Intersection with z=0 plane
    float t = -m_camera.from.z / ray.z;
    m_mouse = m_camera.from + ray * t;
}

void Scene::SetTime(float deltaTime)
{
    m_deltaTime = deltaTime;
    m_current = std::chrono::steady_clock::now();
    m_time = m_current - m_start;
}

std::vector<int> Scene::GetAllActiveIds() const
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

void Scene::MoveCamera(float deltaTime)
{
    float deltaVelocity = deltaTime / 100.0f;

    if (App::IsKeyPressed(VK_NUMPAD6))
    {
        m_camera.from.x += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD4))
    {
        m_camera.from.x -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD8))
    {
        m_camera.from.z -= deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD2))
    {
        m_camera.from.z += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD7))
    {
        m_camera.from.y += deltaVelocity;
    }
    if (App::IsKeyPressed(VK_NUMPAD9))
    {
        m_camera.from.y -= deltaVelocity;
    }
}

void Scene::UpdateVisible()
{
    m_visible.clear();

    std::vector<int> ids = GetAllActiveIds();

    for (auto &id : ids)
    {
        Model model = GetModel(id);
        std::vector<Face> faces = model.GetFaces();

        // Early exit
        if (faces.empty())
        {
            return;
        }

        // Calculate local transform
        Transform transform = GetTransform(id);
        Matrix translate = Matrix::Translate(transform.position);
        Matrix rotate = Matrix::Rotate(transform.rotation);
        Matrix scale = Matrix::Scale(transform.scaling);
        Matrix local = scale * rotate * translate;

        for (auto &face : faces)
        {
            // Apply local transform
            for (int i = 0; i < face.vertices; i++)
            {
                face.vertex[i] = local * face.vertex[i];
            }

            // Apply world transform
            for (int i = 0; i < face.vertices; i++)
            {
                face.vertex[i] = m_world * face.vertex[i];
            }

            // Calculate normal for backface culling
            Vector3 a = face.vertex[1] - face.vertex[0];
            Vector3 b = face.vertex[2] - face.vertex[0];
            Vector3 normal = a.Cross(b).Normalize();

            if (normal.Dot((face.vertex[0] - m_camera.from).Normalize()) < 0.0f)
            {
                // Convert world space to view space
                for (int i = 0; i < face.vertices; i++)
                {
                    face.vertex[i] = m_view * face.vertex[i];
                }

                // Project from 3D to 2D
                for (int i = 0; i < face.vertices; i++)
                {
                    face.vertex[i] = m_projection * face.vertex[i];
                }

                // Normalize with reciprocal divide
                for (int i = 0; i < face.vertices; i++)
                {
                    float w = face.vertex[i].w;
                    if (w != 0.0f)
                    {
                        face.vertex[i] /= w;
                    }
                }

                // Offset into normalized space
                float offsetWidth = m_SCREEN_WIDTH * 0.5f;
                float offsetHeight = m_SCREEN_HEIGHT * 0.5f;
                for (int i = 0; i < face.vertices; i++)
                {
                    face.vertex[i].x = offsetWidth * face.vertex[i].x + offsetWidth;
                    face.vertex[i].y = -offsetHeight * face.vertex[i].y + offsetHeight;
                    face.vertex[i].z = 0.5f * face.vertex[i].z + 0.5f;
                }

                // Add lighting effect
                Vector3 light;
                if (model.light == Light::OUTLINE)
                {
                    light = m_camera.from.Normalize();
                }
                else
                {
                    light = Vector3(0.0f, 0.0f, 1.0f).Normalize();
                }
                model.SetColor(normal.Dot(light), face);

                m_visible.push_back(face);
            }
        }
    }
}

void Scene::SortVisible()
{
    std::sort(m_visible.begin(), m_visible.end(), [](Face &a, Face &b) {
        float z1 = 0.0f;
        float z2 = 0.0f;

        for (int i = 0; i < a.vertices; i++)
        {
            z1 += a.vertex[i].z;
        }
        for (int i = 0; i < b.vertices; i++)
        {
            z2 += b.vertex[i].z;
        }

        z1 /= a.vertices;
        z2 /= b.vertices;

        return z1 > z2;
    });
}

void Scene::RenderVisible()
{
    for (auto &face : m_visible)
    {
        face.Render();
    }
}

void Scene::RenderBorder()
{
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
    float x = 1.0f; // Offset into visible area
    float y = 0.0f;
    float w = m_SCREEN_WIDTH;
    float h = m_SCREEN_HEIGHT - 1.0f; // Offset into visible area
    App::DrawLine(x, y, x, h, r, g, b);
    App::DrawLine(x, h, w, h, r, g, b);
    App::DrawLine(w, h, w, y, r, g, b);
    App::DrawLine(w, y, x, y, r, g, b);
}