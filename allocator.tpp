#include "allocator.hpp"


template<typename T>
T* MyAllocator<T>::allocate(size_t n) {
    if (pool->free_list.empty()) {
        size_t bytes = pool->block_size * pool->element_size;
        void* block = ::operator new(bytes);
        pool->chunks.push_back(block);
        char* base = static_cast<char*>(block);
        pool->free_list.reserve(pool->free_list.size() + pool->block_size);
        for (size_t i = 0; i < pool->block_size; i++)
            pool->free_list.push_back(base + i * pool->element_size);
    }

    void* raw_ptr = pool->free_list.back();
    pool->free_list.pop_back();
    std::cout << "MyAllocator: memory allocate" << std::endl;
    return static_cast<T*>(raw_ptr);
}


    template <typename T>
    void MyAllocator<T>::deallocate(T* ptr, size_t n){
        pool->free_list.push_back(static_cast<void*>(ptr));
        std::cout << "<MyAllocator: memory deallocate" << std::endl;
    }
