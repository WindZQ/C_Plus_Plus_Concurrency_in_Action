#include <atomic>
#include <thread>
#include <assert.h>

std::atomic_bool x, y;
std::atomic_int z;

void write_x_then_y(void)
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x(void)
{
    while(!y.load(std::memory_order_relaxed));
    if(x.load(std::memory_order_relaxed))
        ++z;
}

int main(void)
{
    x = false;
    y = false;
    z = 0;

    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);

    a.join();
    b.join();
    assert(z.load() != 0);

    return 0;
}
