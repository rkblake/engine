#pragma once

#include <cstddef>

namespace memory {

class Allocator {
  public:
    Allocator() {}
    ~Allocator() {}
    virtual void *alloc(size_t bytes) = 0;
    virtual void free(void *ptr) = 0;
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
