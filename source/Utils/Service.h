#pragma once

#include <cassert>

template<typename T>
class Service {
    Service() = delete;

public:
    template<typename... Args>
    static void build(Args&&... args) {
        provide(new T(std::forward<Args>(args)...));
    }

    static void provide(T* ptr) {
        auto& service = storage();
        assert(!service && "Trying to replace a service");
        service = ptr;
    }

    static T& get() {
        auto& service = storage();
        assert(service && "Trying to get a service which was not built");
        return *service;
    }

    static void destroy() {
        auto& service = storage();
        assert(service && "Trying to destroy while service was not built");
        delete service;
        service = nullptr;
    }

    static void clear() {
        auto& service = storage();
        assert(service && "Trying to clear while service was not present");
        service = nullptr;
    }

private:
    static T*& storage() {
        static T* instance = nullptr;
        return instance;
    }
};

template<typename T>
class Provider {
public:
    explicit Provider(T* pointer) {
        Service<T>::provide(pointer);
    }
    ~Provider() {
        Service<T>::clear();
    }
};

template<typename T>
static T& Get() {
    return Service<T>::get();
}
