//
// Created by Eduardo Ribeiro Silva on 08/02/2023.
//

#ifndef OBJECT_POOL_01_OBJECTPOOL_H
#define OBJECT_POOL_01_OBJECTPOOL_H

#include <iostream>
#include <vector>
#include <numeric>

template <typename T, typename Allocator = std::allocator<T>>
class ObjectPool {
public:
    ObjectPool() = default;
    explicit ObjectPool(const Allocator& allocator);
    virtual ~ObjectPool();

    // move constructor and move assignment
    ObjectPool(ObjectPool&& src) noexcept = default;
    ObjectPool& operator=(ObjectPool&& src) noexcept = default;

    // Prevent copy constructor and copy assignment
    ObjectPool(const ObjectPool& src) = delete;
    ObjectPool& operator=(const ObjectPool& src) = delete;

    template<typename... Args>
    std::shared_ptr<T> acquireObject(Args... args);

private:
    void addChunk();

    std::vector<T*> m_pool;
    std::vector<T*> m_free_objects;
    static const size_t ms_initialChunkSize { 5 };
    size_t m_newChunkSize { ms_initialChunkSize };

    Allocator m_allocator;
};

template<typename T, typename Allocator>
ObjectPool<T, Allocator>::ObjectPool(const Allocator &allocator)
        : m_allocator { allocator }
{

}

template<typename T, typename Allocator>
ObjectPool<T, Allocator>::~ObjectPool() {
    using std::pow;

    // Note: this implementation assumes that all objects handed out by this
    //       pool have been returned to the pool before the pool is destroyed.
    //       The following statement asserts if that is not the case
    assert(m_free_objects.size() == ms_initialChunkSize * (pow(2, m_pool.size()) - 1));

    // Deallocate all allocated memory
    size_t chunkSize { ms_initialChunkSize };
    for (auto* chunk: m_pool) {
        m_allocator.deallocate(chunk, chunkSize);
        chunkSize *= 2;
    }

    m_pool.clear();
};

template<typename T, typename Allocator>
void ObjectPool<T, Allocator>::addChunk() {
    using std::cout;
    using std::endl;
    using std::iota;
    using std::begin;
    using std::end;

    cout << "Allocating new chunk..." << endl;

    // Allocate a new chunk of unitialized memory big enough to hold
    // m_newChunkSize instances of T, and add the chunk to the pool
    auto* firstNewObject { m_allocator.allocate(m_newChunkSize) };
    m_pool.push_back(firstNewObject);

    // Create pointers to each individual object in the new chunk
    // and store them in the list of free objects
    auto oldFreeObjectsSize { m_free_objects.size() };
    m_free_objects.resize(oldFreeObjectsSize + m_newChunkSize);
    iota(begin(m_free_objects) + oldFreeObjectsSize, end(m_free_objects), firstNewObject);

    // Double the chunk size for the next time
    m_newChunkSize *= 2;
}

template<typename T, typename Allocator>
template<typename... Args>
std::shared_ptr<T> ObjectPool<T, Allocator>::acquireObject(Args... args) {
    using std::forward;
    using std::shared_ptr;
    using std::destroy_at;

    // If there are no free objects, allocate a new chunk
    if (m_free_objects.empty()) {
        addChunk();
    }

    // Get a free object
    T* object { m_free_objects.back() };

    // Initialize, i.e. construct, an instance of T in an
    // uninitialized block of memory using placement new, and
    // perfectly forward any provided arguments to the constructor
    new(object) T {forward<Args>(args)... };

    // Remove the object from the list of free objects
    m_free_objects.pop_back();

    // Wrap the initialized object and return it
    return shared_ptr<T> { object, [this](T* object) {
        // Destroy object
        destroy_at(object);
        // Put the object back in the list of free objects
        m_free_objects.push_back(object);
    }};
}


#endif //OBJECT_POOL_01_OBJECTPOOL_H
