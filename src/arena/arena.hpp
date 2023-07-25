#pragma once

#include <cstddef>

namespace memory {

class Allocator {
  protected:
    size_t size;

  public:
    Allocator(size_t size) {}
    ~Allocator() {}
    virtual void *alloc(size_t bytes) = 0;
    virtual void free(void *ptr) = 0;
};

class StackAllocator : public Allocator {
  private:
    size_t top;

  public:
    void *alloc(size_t bytes);
    void free(void *ptr);
};

class BuddyAllocator : public Allocator {
  public:
    void *alloc(size_t bytes);
    void free(void *ptr);
};

class Arena {
  private:
    void *data;
    size_t reserved;
    Allocator *allocator;

  public:
    Arena(Allocator *allocator, size_t initial_size);
    ~Arena();

    void *alloc(size_t bytes);
    void free(void *ptr);
};

} // namespace memory
