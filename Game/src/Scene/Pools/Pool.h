#pragma once

#include <vector>

class Scene;

class Pool
{
  public:
    Pool();

    virtual void Init(Scene &scene) = 0;

    std::vector<size_t> GetActiveEntities();

    bool Activate(int index);
    bool Deactivate(int index);

  protected:
    void SetScene(Scene *scene);
    void SetBegin(size_t index);
    void SetSize(size_t index);
    void SetEnd(size_t index);

  private:
    Scene *m_scene;
    size_t m_begin;
    size_t m_size;
    size_t m_end;

    void MemorySwap(int index);
};