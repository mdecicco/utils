#pragma once
#include <utils/Singleton.h>
#include <utils/Thread.h>

namespace utils {
    template <typename T>
    T* Singleton<T>::instance = nullptr;

    template <typename T>
    template <typename ...Args>
    void Singleton<T>::Create(Args ...args) {
        if (instance) return;
        instance = new T(args...);
    }

    template <typename T>
    void Singleton<T>::Destroy() {
        if (instance) delete instance;
        instance = nullptr;
    }

    template <typename T>
    T* Singleton<T>::Get() {
        return instance;
    }

    
    template <typename T>
    PerThreadSingleton<T>* PerThreadSingleton<T>::instance = nullptr;

    template <typename T>
    template <typename F>
    void PerThreadSingleton<T>::Create(F&& creatorFunc) {
        if (instance) return;
        instance = new PerThreadSingleton<T>(creatorFunc);
    }
    
    template <typename T>
    std::enable_if_t<std::is_constructible_v<T>>
    PerThreadSingleton<T>::Create() {
        if (instance) return;
        instance = new PerThreadSingleton<T>([](){ return new T(); });
    }

    template <typename T>
    template <typename F>
    PerThreadSingleton<T>::PerThreadSingleton(F&& creatorFunc) : m_newInstanceFunc(creatorFunc) {
    }

    template <typename T>
    PerThreadSingleton<T>::~PerThreadSingleton() {
        for (auto it : m_instanceMap) delete it.second;
    }

    template <typename T>
    void PerThreadSingleton<T>::Destroy() {
        if (instance) delete instance;
        instance = nullptr;
    }

    template <typename T>
    void PerThreadSingleton<T>::Destroy(thread_id tid) {
        std::unique_lock<std::shared_mutex> lock(instance->m_mapLock);
        auto it = instance->m_instanceMap.find(tid);
        if (it == instance->m_instanceMap.end()) return;
        delete it->second;
        instance->m_instanceMap.erase(it);
    }

    template <typename T>
    T* PerThreadSingleton<T>::Get() {
        thread_id tid = Thread::Current();

        {
            std::shared_lock<std::shared_mutex> lock(instance->m_mapLock);
            auto it = instance->m_instanceMap.find(tid);
            if (it != instance->m_instanceMap.end()) return it->second;
        }

        std::unique_lock<std::shared_mutex> lock(instance->m_mapLock);
        T* a = instance->m_newInstanceFunc();
        instance->m_instanceMap[tid] = a;
        return a;
    }
};