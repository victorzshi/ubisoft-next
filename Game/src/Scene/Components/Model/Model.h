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

struct Model
{
    Mesh mesh;
    Color color;

    Model();

    std::vector<Face> GetFaces();

  private:
    static std::vector<Face> m_cube;
    static std::vector<Face> m_sphere;
    static std::vector<Face> m_torus;
    static std::vector<Face> m_plane;

    static std::vector<Face> LoadFromObjectFile(std::string file);
};