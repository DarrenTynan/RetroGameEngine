//
// Created by Darren Tynan on 10/12/2024.
//

#ifndef RETROGAMEENGINE_COMPONENT_H
#define RETROGAMEENGINE_COMPONENT_H

const unsigned int MAX_COMPONENTS = 32;

/**
 * We use a bitset (1s and 0s) to keep track of which components an entity has,
 * and also helps keep track of which entities a system is interested in.
 */
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
protected:
    static int nextId;
};


/**
 * @brief Used to assign a unique id to a component type
 *
 * Return the unique id of Component<T>
 *
 * @tparam T
 */
template <typename T>
class Component: public IComponent {
public:
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
};

#endif //RETROGAMEENGINE_COMPONENT_H
