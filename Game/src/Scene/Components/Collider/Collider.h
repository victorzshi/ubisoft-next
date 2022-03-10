#pragma once

class Scene;

struct Collider
{
    float radius;

    Collider();

    static bool IsHit(Scene &scene, int a, int b);
};