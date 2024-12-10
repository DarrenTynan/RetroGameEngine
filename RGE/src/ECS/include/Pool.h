//
// Created by Darren Tynan on 10/12/2024.
//

#ifndef RETROGAMEENGINE_POOL_H
#define RETROGAMEENGINE_POOL_H

/**
 * @brief IPool is just a vector (contiguous data) of objects of type T
 */
class IPool {
public:
    virtual ~IPool() = default;
};


/**
 * @brief A Pool class to hold pointers to entities spawned.
 *
 * @tparam T
 */
template <typename T>
class Pool: public IPool {
private:
    std::vector<T> data;

public:
    explicit Pool(int size = 100) { data.resize(size); }
    ~Pool() override = default;

    [[nodiscard]] bool IsEmpty() const { return data.empty(); }
    [[nodiscard]] int GetSize() const { return data.size(); }
    void Resize(int n) { data.resize(n); }
    void Clear() { data.clear(); }
    void Add(T object) { data.push_back(object); }
    void Set(int index, T object) { data[index] = object; }
    T& Get(int index) { return static_cast<T&>(data[index]); }
    T& operator [](unsigned int index) { return data[index]; }
};

#endif //RETROGAMEENGINE_POOL_H
