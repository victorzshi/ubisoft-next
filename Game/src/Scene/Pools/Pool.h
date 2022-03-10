#pragma once

#include <vector>

class Scene;

class Pool
{
  public:
    Pool();
    virtual ~Pool() = default;

    virtual void Init(Scene &scene) = 0;

    virtual void UpdateIds(Scene &scene) = 0;

    std::vector<int> GetIds() const;

  protected:
    Scene *GetScene() const;

    /*
        BEGIN    SIZE    END       pointers
          v       v       v
     ...  4   5   6   7   8  ...   array indexes
    | - | X | X | - | - | - | - |  contiguous array

    X = active data
    - = inactive data

    In this case, there are two active indexes at 4 and 5.
    Therefore the size of the pool is 2.
    However, to get the correct array index:

    SIZE = total active + array's first index
    SIZE = 2 + BEGIN
    SIZE = 2 + 4
    SIZE = 6

    Since Pool keeps the array sorted:
      1. index < size are active
      2. index >= size are inactive

    GetBegin(): Returns first valid index of the allocated array.
    GetSize(): Returns current size plus offset. Equivalent to first inactive index of the allocated array.
    GetEnd(): Returns last valid index of the allocated array.
    */

    int GetBegin() const;
    int GetSize() const;
    int GetEnd() const;

    void SetScene(Scene *scene);
    void SetBegin(int id);
    void SetSize(int id);
    void SetEnd(int id);

    // Manage memory and keep data packed
    bool Activate(int id);
    bool Deactivate(int id);

  private:
    Scene *m_scene;
    int m_begin;
    int m_size;
    int m_end;

    void SwapMemory(int id);
};