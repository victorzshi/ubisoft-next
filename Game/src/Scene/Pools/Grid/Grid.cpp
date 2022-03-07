#include "stdafx.h"

#include "Grid.h"

#include "Scene/Scene.h"

void Grid::Init(Scene &scene)
{
    Mesh mesh = Mesh::LoadFromObjectFile(FILE);

    int index = 0;
    std::vector<Vector3> positions = CreatePositions();
    for (auto &position : positions)
    {
        int id = scene.CreateId();

        scene.SetMesh(id, mesh);

        Transform transform;
        transform.position = position;
        transform.rotation.x = 90.0f;
        transform.scaling = Vector3(0.9f, 0.9f, 0.9f);
        scene.SetTransform(id, transform);

        index = id;
    }

    SetScene(&scene);
    SetBegin(index - (ROWS * COLUMNS - 1));
    SetSize(index + 1);
    SetEnd(index);
}

std::vector<Vector3> Grid::CreatePositions()
{
    // Cube model should be unit cube.
    float WIDTH = 1.0f;
    float HEIGHT = 1.0f;

    float gridWidth = WIDTH * COLUMNS;
    float gridHeight = HEIGHT * ROWS;

    // World origin
    float centerX = 0.0f;
    float centerY = 0.0f;

    // Offset to top left corner
    float startX = centerX - gridWidth / 2 + WIDTH / 2;
    float startY = centerY - gridHeight / 2 + HEIGHT / 2;

    float spawnX = startX;
    float spawnY = startY;

    std::vector<Vector3> positions;
    for (int i = 0; i < ROWS * COLUMNS; i++)
    {
        Vector3 position;

        position.x = spawnX;
        position.y = spawnY;

        positions.push_back(position);

        spawnX += WIDTH;
        if ((i + 1) % COLUMNS == 0)
        {
            spawnX = startX;
            spawnY += HEIGHT;
        }
    }

    return positions;
}