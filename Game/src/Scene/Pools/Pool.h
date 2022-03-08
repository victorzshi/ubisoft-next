#pragma once

#include <vector>

class Scene;

class Pool
{
  public:
    Pool();
    virtual ~Pool() = default;

    virtual void Init(Scene &scene) = 0;

    int GetNextId() const;
    std::vector<int> GetActiveIds() const;

    bool Activate(int id);
    bool Deactivate(int id);

  protected:
    Scene *GetScene() const;

    void SetScene(Scene *scene);
    void SetBegin(int id);
    void SetSize(int id);
    void SetEnd(int id);

  private:
    Scene *m_scene;
    int m_begin;
    int m_size;
    int m_end;

    void SwapMemory(int id);
};