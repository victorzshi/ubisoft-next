#pragma once

#include "Graphics/Face/Face.h"

enum class Meshes
{
    PLANE,
    CUBE,
    SPHERE,
    ICOSPHERE,
    CONE,
    TORUS,
    MONKEY,
};

struct Mesh
{
  public:
    Mesh();

    std::vector<Face> GetFaces();

    void SetMesh(Meshes mesh);

  private:
    Meshes m_mesh;

    static std::vector<Face> m_plane;
    static std::vector<Face> m_cube;
    static std::vector<Face> m_sphere;
    static std::vector<Face> m_icosphere;
    static std::vector<Face> m_cone;
    static std::vector<Face> m_torus;
    static std::vector<Face> m_monkey;

    static std::vector<Face> LoadFromObjectFile(std::string file);
};