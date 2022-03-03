#include "stdafx.h"

#include "Triangle.h"

Triangle::Triangle()
{
    for (int i = 0; i < 3; i++)
    {
        point[i] = Vector3();
    }
}

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3)
{
    point[0] = p1;
    point[1] = p2;
    point[2] = p3;
}

void Triangle::Render()
{
    for (int i = 0; i < 3; i++)
    {
        int a = i;
        int b = (i + 1) % 3;
        float sx = point[a].x;
        float sy = point[a].y;
        float ex = point[b].x;
        float ey = point[b].y;
        App::DrawLine(sx, sy, ex, ey);
    }
}