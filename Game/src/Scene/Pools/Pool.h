#pragma once

class Scene;

class Pool
{
  public:
    Pool();

    virtual void Init(Scene &scene) = 0;

    // TODO: GetActive() return vector of size_t ids.
    size_t Begin();
    size_t Size();
    size_t End();

    bool Activate(int index);
    bool Deactivate(int index);

  protected:
    size_t m_begin;
    size_t m_size;
    size_t m_end;

    void SetScene(Scene *scene);

  private:
    Scene *m_scene;

    void MemorySwap(int index);
};