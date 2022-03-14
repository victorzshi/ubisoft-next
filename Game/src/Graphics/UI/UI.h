#pragma once

#include "Graphics/Color/Color.h"

#include <chrono>

class Scene;
class Renderer;

enum class Screen
{
    START,
    NONE,
    PAUSED,
    GAME_OVER,
};

struct Scoring
{
    bool isWin = false;
    int damageTaken = 0;
    int enemiesDestroyed = 0;
    std::chrono::duration<float> totalTime;

    void Reset()
    {
        isWin = false;
        damageTaken = 0;
        enemiesDestroyed = 0;
        totalTime = totalTime.zero();
    }
};

class UI
{
  public:
    Scoring scoring;

    UI();

    void Init(Scene &scene, Renderer &renderer);

    Screen GetScreen() const;

    void SetScreen(Screen screen);

    void HandleInput();

    void Update();

    void Render();

  private:
    void *m_FONT = GLUT_BITMAP_9_BY_15;

    Scene *m_scene;
    Renderer *m_renderer;

    Screen m_screen;
    Color m_colorLife;
    Color m_colorFuel;
    std::string m_life;
    std::string m_fuel;
    std::chrono::time_point<std::chrono::steady_clock> m_paused;
    std::chrono::time_point<std::chrono::steady_clock> m_pressed;
    std::chrono::time_point<std::chrono::steady_clock> m_current;
    std::chrono::duration<float> m_time;
    bool m_isHidden;

    Color GetTextColor(int level);
    void PrintShipStats();
};