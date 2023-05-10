#include <iostream>


size_t memoryUsage = 0;

struct MemData {
	size_t size;
};

void* operator new(size_t size) {
    memoryUsage += size;
    void* ptr = std::malloc(size + sizeof(MemData));
    *reinterpret_cast<MemData*>(ptr) = MemData{ size };
    ptr = reinterpret_cast<char*>(ptr) + sizeof(MemData);
    if (!ptr) throw std::bad_alloc();
    return ptr;
}

void operator delete(void* ptr) noexcept {
    ptr = reinterpret_cast<char*>(ptr) - sizeof(MemData);
	size_t size = reinterpret_cast<MemData*>(ptr)->size;
	memoryUsage -= size;
    std::free(ptr);
}