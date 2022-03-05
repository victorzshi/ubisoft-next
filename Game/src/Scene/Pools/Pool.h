#pragma once

#include <vector>

class Scene;

class Pool
{
  public:
    Pool();

    virtual void Init(Scene &scene) = 0;

    std::vector<int> GetIds();

    bool Activate(int id);
    bool Deactivate(int id);

  protected:
    void SetScene(Scene *scene);
    void SetBegin(int id);
    void SetSize(int id);
    void SetEnd(int id);

  private:
    Scene *m_scene;
    int m_begin;
    int m_size;
    int m_end;

    void MemorySwap(int id);
};