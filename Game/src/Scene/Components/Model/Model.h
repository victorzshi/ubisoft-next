#pragma once

#include <string>
#include <vector>

#include "Graphics/Face/Face.h"

enum class Mesh
{
    CUBE,
    SPHERE,
    TORUS,
    PLANE,
};

enum class Color
{
    WHITE,
    GREY,
    RED,
    GREEN,
    BLUE,
};

enum class Light
{
    BRIGHT,
    SHADOW,
    OUTLINE,
};

struct Model
{
    Mesh mesh;
    Color color;
    Light light;

    Model();

    std::vector<Face> GetFaces();

    void SetColor(float dot, Face &face);

  private:
    static std::vector<Face> m_cube;
    static std::vector<Face> m_sphere;
    static std::vector<Face> m_torus;
    static std::vector<Face> m_plane;

    static std::vector<Face> LoadFromObjectFile(std::string file);
};