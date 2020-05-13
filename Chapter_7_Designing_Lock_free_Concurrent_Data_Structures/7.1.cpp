#include <atomic>

class spinlock_mutex
{
    std::atomic_flag flag;
public:
    spinlock_mutex()
        : flag(ATOMIC_FLAG_INIT)
    {}

    void lock(void)
    {
        while(flag.test_and_set(std::memory_order_acquire));
    }

    void unlock(void)
    {
        flag.clear(std::memory_order_release);
    }
};
