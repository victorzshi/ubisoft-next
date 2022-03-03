#include "stdafx.h"

#include "Scene.h"

Scene::Scene() : viewport_({0.0f, 0.0f, 0.0f, 0.0f})
{
    // TODO: Allocate component arrays
}

Scene::~Scene()
{
    // TODO: Clean up stuff
}

void Scene::Init(Box viewport)
{
    viewport_ = viewport;

    float fov = 90.0f;
    float aspectRatio = viewport.w / viewport.h;
    float zNear = 0.1f;
    float zFar = 100.0f;
    projection_ = Matrix::Perspective(fov, aspectRatio, zNear, zFar);

    mesh_ = Mesh::Cube();
}

void Scene::Update(float deltaTime)
{
    HandleInput();

    static float elapsed = 0.0f;
    elapsed += deltaTime / 1000.0f;

    Matrix scaling = Matrix::Scale(1.0f, 1.0f, 1.0f);
    // Matrix rotation = Matrix::RotateY(elapsed) * Matrix::RotateX(elapsed);
    Matrix rotation = Matrix::Identity();
    Matrix translation = Matrix::Translate(Vector3(0.0f, 0.0f, 5.0f));
    Matrix world = Matrix::Identity() * scaling * rotation * translation;

    // Set up camera
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 target = Vector3(0.0f, 0.0f, 1.0f);
    Vector3 lookDirection = Matrix::RotateY(camera_.yaw) * target;
    target = camera_.position + lookDirection;
    Matrix camera = Matrix::PointAt(camera_.position, target, up);
    Matrix view = Matrix::QuickInverse(camera);

    std::vector<Triangle> raster;
    for (auto &triangle : mesh_.triangles)
    {
        Triangle transformed;

        // Apply tranformation
        for (int i = 0; i < 3; i++)
        {
            transformed.point[i] = world * triangle.point[i];
        }

        // Calculate normal
        Vector3 a = transformed.point[1] - transformed.point[0];
        Vector3 b = transformed.point[2] - transformed.point[0];
        Vector3 normal = a.Cross(b).Normalize();

        if (normal.Dot((transformed.point[0] - camera_.position).Normalize()) < 0.0f)
        {
            Triangle viewed;

            // Convert world space to view space
            for (int i = 0; i < 3; i++)
            {
                viewed.point[i] = view * transformed.point[i];
            }

            Triangle projected;

            // Project from 3D to 2D
            for (int i = 0; i < 3; i++)
            {
                projected.point[i] = projection_ * viewed.point[i];
            }

            // Normalize with reciprocal divide
            for (int i = 0; i < 3; i++)
            {
                float w = projected.point[i].w;
                assert(w != 0.0f);
                projected.point[i] /= w;
            }

            // Offset into normalized space
            Vector3 offset = Vector3(1.0f, 1.0f, 0.0f);
            for (int i = 0; i < 3; i++)
            {
                projected.point[i] += offset;
                projected.point[i].x *= viewport_.w * 0.5f;
                projected.point[i].y *= viewport_.h * 0.5f;
            }

            raster.push_back(projected);
        }
    }

    triangles_ = raster;
}

void Scene::Render()
{
#ifdef _DEBUG
    DrawBorder();
#endif

    for (auto &triangle : triangles_)
    {
        triangle.Render();
    }

    float x = viewport_.w * 0.01f;
    float y = viewport_.h * 0.95f;
    App::Print(x, y, "Scene::Render()");
}

void Scene::DrawBorder()
{
    float r = 0.0f;
    float g = 1.0f;
    float b = 0.0f;
    float x = viewport_.x + 1.0f; // Offset into visible area
    float y = viewport_.y;
    float w = viewport_.w;
    float h = viewport_.h - 1.0f; // Offset into visible area
    App::DrawLine(x, y, x, h, r, g, b);
    App::DrawLine(x, h, w, h, r, g, b);
    App::DrawLine(w, h, w, y, r, g, b);
    App::DrawLine(w, y, x, y, r, g, b);
}

void Scene::HandleInput()
{
    if (App::GetController().GetLeftThumbStickX() > 0.5f)
    {
        camera_.position.x -= 0.05f;
    }
    if (App::GetController().GetLeftThumbStickX() < -0.5f)
    {
        camera_.position.x += 0.05f;
    }
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        camera_.position.y += 0.05f;
    }
    if (App::GetController().GetLeftThumbStickY() < -0.5f)
    {
        camera_.position.y -= 0.05f;
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
    {
        camera_.yaw += 0.05f;
    }
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
    {
        camera_.yaw -= 0.05f;
    }
}
