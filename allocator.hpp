#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <new>

template <typename T>
class MyAllocator{
    public:
        using value_type = T;

        template <typename U>
        struct rebind {
            using other = MyAllocator<U>;
        };
        
        T* allocate(size_t n);

        void deallocate(T* ptr, size_t n);


    private:
        template<typename> friend class MyAllocator;
        struct PoolData {
            const size_t block_size; //сколько элементов выделять за раз
            size_t element_size; //размер одного элемента
            std::vector<void*> chunks; //сырые блоки памяти
            std::vector<void*> free_list; //список указателей на свободные блоки

            PoolData(size_t bsize, size_t esize) : block_size(bsize), element_size(esize) {}
            ~PoolData() {
                for (void* p : chunks) {
                    ::operator delete(p);
            }
        }
    };

        std::shared_ptr<PoolData> pool;


    public:
        explicit MyAllocator(size_t block_size = 10): pool(std::make_shared<PoolData>(block_size, sizeof(T))) {} //конструктор
        
        template<typename U>
        bool operator==(const MyAllocator<U>& other) const noexcept{
            return pool == other.pool;
        }
        template<typename U>
        bool operator!=(const MyAllocator<U>& other) const noexcept{
            return !(*this == other);
        }

        template <typename U>
        MyAllocator(const MyAllocator<U>& other) noexcept: pool(std::make_shared<PoolData>(other.pool->block_size, sizeof(T))) {}

        MyAllocator(const MyAllocator& other) noexcept = default;

};

#include "allocator.tpp"