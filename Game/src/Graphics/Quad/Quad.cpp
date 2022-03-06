#include "stdafx.h"

#include "Quad.h"

Quad::Quad() : point{Vector3()}
{
}

void Quad::Render()
{
    for (int i = 0; i < 4; i++)
    {
        int a = i;
        int b = (i + 1) % 4;
        float sx = point[a].x;
        float sy = point[a].y;
        float ex = point[b].x;
        float ey = point[b].y;
        App::DrawLine(sx, sy, ex, ey);
    }
}