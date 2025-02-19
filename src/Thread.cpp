#include <utils/Thread.h>
#include <utils/Array.hpp>
#include <utils/Singleton.hpp>

#ifdef _WIN32
    #include <Windows.h>
#elif defined(__linux__)
    #include <sys/prctl.h>
#endif

namespace utils {
    //
    // Thread
    //

    Thread::Thread(const std::function<void()>& entry) {
        m_isRunning = false;
        reset(entry);
    }

    Thread::Thread() {
        m_isRunning = false;
    }

    Thread::~Thread() {
        if (m_thread.joinable()) m_thread.join();
    }

    thread_id Thread::getId() const {
        return std::hash<std::thread::id>{}(m_thread.get_id());
    }

    void Thread::setName(const char* name) {
        #ifdef __MINGW32__
            // For some insane reason, my mingw setup has zero APIs for this.
            abort();
        #elif _WIN32
            wchar_t buf[256] = { 0 };
            if (MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name, -1, buf, 256) > 0) {
                SetThreadDescription(static_cast<HANDLE>(m_thread.native_handle()), buf);
            }
        #elif defined(__linux__)
            abort();
        #else
            pthread_setname_np(m_thread.native_handle(), name);
        #endif
    }

    void Thread::reset(const std::function<void()>& entry) {
        if (m_thread.joinable() && isRunning()) m_thread.join();
        m_thread = std::thread([this, entry](){
            this->m_isRunningMutex.lock();
            this->m_isRunning = true;
            this->m_isRunningMutex.unlock();

            entry();
            
            this->m_isRunningMutex.lock();
            this->m_isRunning = false;
            this->m_isRunningMutex.unlock();
        });
    }

    void Thread::setAffinity(u32 cpuIdx) {
        if (Thread::Current() != getId()) {
            return;
        }

        #ifdef __MINGW32__
            // For some insane reason, my mingw setup has zero APIs for this.
            abort();
        #elif _WIN32
        HANDLE thread = (HANDLE)m_thread.native_handle();
        DWORD_PTR r = SetThreadAffinityMask(thread, DWORD_PTR(1) << cpuIdx);
        if (r == 0) {
            DWORD error = GetLastError();
            if (error) {
                LPVOID lpMsgBuf;
                DWORD bufLen = FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    error,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR)&lpMsgBuf,
                    0, 
                    NULL
                );
                if (bufLen) {
                    LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
                    std::string result(lpMsgStr, lpMsgStr+bufLen);

                    LocalFree(lpMsgBuf);

                    printf("SetThreadAffinityMask failed: %s\n", result.c_str()); 
                }
                else printf("SetThreadAffinityMask failed\n"); 
            }
            else printf("SetThreadAffinityMask failed\n"); 
        }
        #endif
    }

    void Thread::waitForExit() {
        if (!m_thread.joinable() || !isRunning()) return;
        m_thread.join();
    }

    bool Thread::isRunning() {
        m_isRunningMutex.lock();
        bool result = m_isRunning;
        m_isRunningMutex.unlock();
        return result;
    }

    thread_id Thread::Current() {
        return std::hash<std::thread::id>{}(std::this_thread::get_id());
    }

    void Thread::Sleep(u32 ms) {
        std::this_thread::sleep_for(std::chrono::duration<u32, std::milli>(ms));
    }

    u32 Thread::MaxHardwareThreads() {
        return std::thread::hardware_concurrency();
    }

    u32 Thread::CurrentCpuIndex() {
        #ifdef __MINGW32__
            // For some insane reason, my mingw setup has zero APIs for this.
            abort();
        #elif _WIN32
            return GetCurrentProcessorNumber();
        #else
            return 0;
        #endif
    }



    //
    // Thread
    //

    Worker::Worker() : m_id(0), m_doStop(false), m_thread() {
    }

    Worker::~Worker() {
        m_doStop = true;
    }

    void Worker::start(WorkerId id, u32 cpuIdx) {
        m_id = id;
        m_thread.reset([this, cpuIdx]{
            m_thread.setAffinity(cpuIdx);
            run();
        });
    }

    void Worker::run() {
        printf("Worker %d: Running on CPU %d.\n", m_id, Thread::CurrentCpuIndex());
        fflush(stdout);

        sThreadPool* tp = ThreadPool::Get();
        while (!m_doStop) {
            tp->waitForWork(this);

            Job* j = tp->getWork();
            if (j) {
                j->run();
                tp->release(j);
            }
        }
        printf("Worker(id: %d, cpu: %d) terminated.\n", m_id, Thread::CurrentCpuIndex());
        fflush(stdout);
    }

    
    
    //
    // Job
    //

    Job::Job(std::function<void()> cb) : m_cb(cb) { }

    Job::~Job() { }

    void Job::run() {
        m_cb();
    }



    //
    // ThreadPool
    //
    FixedAllocator<Job>* sThreadPool::allocatorPageGenerator() {
        return new FixedAllocator<Job>(512, 512);
    }

    sThreadPool::sThreadPool() : m_jobAllocator(allocatorPageGenerator) {
        u32 wc = Thread::MaxHardwareThreads();
        m_workers = new Worker[wc];
        for (u32 i = 0;i < wc;i++) m_workers[i].start(i + 1, i);
    }

    sThreadPool::~sThreadPool() {
        u32 wc = Thread::MaxHardwareThreads();
        for (u32 i = 0;i < wc;i++) m_workers[i].m_doStop = true;
        m_workCondition.notify_all();

        delete [] m_workers;
    }

    Job* sThreadPool::getWork() {
        Job* ret = nullptr;
        m_jobMutex.lock();
        if (m_pending.size() > 0) ret = m_pending.pop();
        m_jobMutex.unlock();

        return ret;
    }

    void sThreadPool::release(Job* j) {
        m_jobMutex.lock();
        m_jobAllocator.free(j);
        m_jobMutex.unlock();
    }

    bool sThreadPool::hasWork() const {
        return m_pending.size() > 0;
    }

    void sThreadPool::waitForWork(Worker* w) {
        if (m_pending.size() > 0) return;
        std::unique_lock<std::mutex> l(m_jobMutex);
        m_workCondition.wait(l, [this, w]{ return w->m_doStop || m_pending.size() > 0; });
    }
};