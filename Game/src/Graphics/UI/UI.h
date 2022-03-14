#pragma once

#include "Graphics/Color/Color.h"

#include <chrono>

enum class Screen
{
    START,
    NONE,
    PAUSED,
};

class Scene;

class UI
{
  public:
    UI();

    void Init(Scene *scene, float SCREEN_WIDTH, float SCREEN_HEIGHT);

    Screen GetScreen() const;

    void SetScreen(Screen screen);

    void HandleInput();

    void Update();

    void Render();

  private:
    void *m_FONT = GLUT_BITMAP_9_BY_15;
    float m_SCREEN_WIDTH;
    float m_SCREEN_HEIGHT;

    Scene *m_scene;
    Screen m_screen;
    Color m_colorLife;
    Color m_colorFuel;
    std::string m_life;
    std::string m_fuel;
    std::chrono::time_point<std::chrono::steady_clock> m_pressed;
    std::chrono::time_point<std::chrono::steady_clock> m_current;
    std::chrono::duration<float> m_time;
    bool m_isHidden;

    Color GetTextColor(int level);
    void PrintShipStats();
};