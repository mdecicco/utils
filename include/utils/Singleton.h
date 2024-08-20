#pragma once
#include <utils/Types.h>
#include <utils/robin_hood.h>

#include <functional>
#include <shared_mutex>

namespace utils {
    template <typename T>
    class Singleton {
        public:
            template <typename ...Args>
            static void Create(Args ...args);

            static void Destroy();

            static T* Get();

        private:
            static T* instance;
    };

    
    template <typename T>
    class PerThreadSingleton {
        public:
            template <typename F>
            static void Create(F&& creatorFunc);

            static std::enable_if_t<std::is_constructible_v<T>>
            Create();

            // Destroys self and all per-thread instances
            static void Destroy();

            // Destroys _only_ the per-thread instance that corresponds to 'tid'
            static void Destroy(thread_id tid);

            static T* Get();

        protected:
            virtual ~PerThreadSingleton();
        
        private:
            static PerThreadSingleton<T>* instance;

            template <typename F>
            PerThreadSingleton(F&& creatorFunc);

            // Hash map of thread id -> PageAllocatorTp*
            std::shared_mutex m_mapLock;
            robin_hood::unordered_map<thread_id, T*> m_instanceMap;
            std::function<T*()> m_newInstanceFunc;
    };
};