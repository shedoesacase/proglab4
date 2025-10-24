#pragma once
#include <memory>
#include "allocator.hpp"

template<typename T, typename Allocator = MyAllocator<T>>

class SingleList {
    private:
        struct Node{
            T value;
            Node* next;
            Node(const T& val) : value(val), next(nullptr) {}
        };

        using node_alloc_t = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
        node_alloc_t node_alloc;
        Node* head;
        size_t size;

    public:
        SingleList() : head(nullptr), size(0) {}
        SingleList(SingleList&& other){
            head = std::move(other.head);
            size = other.size;
            other.size =0;
        }
        ~SingleList() {
            clear();
        }

        void clear() {
            Node* cur = head;
            while (cur){
                Node* next = cur->next;

                std::allocator_traits<node_alloc_t>::destroy(node_alloc, cur);
                std::allocator_traits<node_alloc_t>::deallocate(node_alloc, cur, 1);

                cur = next;
            }

            head = nullptr;
            size = 0;
        }

        SingleList operator=(SingleList&& other){
            if(this == &other){
                return *this;
            }
            clear(); // очищаем старые данные
            head = other.head;
            size = other.size;
            other.head = nullptr;
            other.size =0;
            return *this;
        }

        void push_back(const T& value){

            Node* newNode = std::allocator_traits<node_alloc_t>::allocate(node_alloc, 1);
            std::allocator_traits<node_alloc_t>::construct(node_alloc, newNode, value);
            newNode->next = nullptr;
            if(size == 0){
                head = newNode; //пустой список
                size++;
            }
            else{
            Node* cur = head; //первый элемент
            while(cur->next != nullptr){ //пока следующий не пустой
                cur = cur->next; //присваиваем следующий
            }
            cur->next = newNode; //присваиваем к последнему наш элемент
            size++;
            }
        }

        void push_back(T&& value){
            Node* newNode = std::allocator_traits<node_alloc_t>::allocate(node_alloc, 1);
            std::allocator_traits<node_alloc_t>::construct(node_alloc, newNode, std::move(value));
            newNode->next = nullptr;
            if(size == 0){
                head = newNode; //пустой список
                size++;
            }
            else{
            Node* cur = head; //первый элемент
            while(cur->next != nullptr){ //пока следующий не пустой
                cur = cur->next; //присваиваем следующий
            }
            cur->next = newNode; //присваиваем к последнему наш элемент
            size++;
            }
        }

        void insert(size_t index, const T& value){
            if(index > size) return;
            Node* newNode = std::allocator_traits<node_alloc_t>::allocate(node_alloc, 1);
            std::allocator_traits<node_alloc_t>::construct(node_alloc, newNode, std::move(value));
            if(index == 0){
                newNode->next = head;
                head = newNode; //пустой список
                size++;
            }
            else{
            Node* cur = head; //первый элемент
            for(size_t i = 0; i < index - 1; i++){
                cur = cur->next;
            }
            newNode->next =cur->next;
            cur->next = newNode; //присваиваем к последнему наш элемент
            size++;
        } 
    }

        void insert(size_t index, T&& value){
            if(index > size) return;
            Node* newNode = std::allocator_traits<node_alloc_t>::allocate(node_alloc, 1);
            std::allocator_traits<node_alloc_t>::construct(node_alloc, newNode, std::move(value));
            if(index == 0){
                newNode->next = head;
                head = newNode; //пустой список
                size++;
            }
            else{
            Node* cur = head; //первый элемент
            for(size_t i = 0; i < index - 1; i++){
                cur = cur->next;
            }
            newNode->next = cur->next;
            cur->next = newNode; //присваиваем к последнему наш элемент
            size++;
        } 
    }

    void erase (size_t index){
        if(index >= size) return;
        Node* to_del = nullptr;
        if(index == 0){
            to_del = head;
            head = head->next;
            size--;
        }
        else{
        Node* cur = head;
        for(size_t i = 0; i < index - 1; i++){
            cur = cur->next;
        }
        to_del = cur->next;
        cur->next = cur->next->next;
        size--;
        }
        std::allocator_traits<node_alloc_t>::destroy(node_alloc, to_del);
        std::allocator_traits<node_alloc_t>::deallocate(node_alloc, to_del, 1);

    }

    std::size_t getsize() const { //геттер сайза
    return size;
    }

    T& operator[] (size_t index){
        Node* cur = head;
        for(size_t i = 0; i < index; i++){
            cur = cur->next;
        }
        return cur->value;
    }

    class Iterator{
        Node* ptr;
        public:
            Iterator(Node* n) : ptr(n) {}
            T& operator*() {return ptr->value;} //разыменовывание
            Iterator& operator++() {
                ptr = ptr->next.get();
                return *this;
            }
        bool operator!=(const Iterator& other) {return ptr != other.ptr; }
    };
    Iterator begin(){return Iterator(head.get());}
    Iterator end(){return Iterator(nullptr);}

};