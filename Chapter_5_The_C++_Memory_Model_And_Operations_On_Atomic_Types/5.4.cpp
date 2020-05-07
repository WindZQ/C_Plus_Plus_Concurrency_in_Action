#include <atomic>
#include <thread>
#include <assert.h>

std::atomic_bool x, y;
std::atomic_int z;

void write_x(void)
{
    x.store(true, std::memory_order_seq_cst);
}

void write_y(void)
{
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y(void)
{
    while(!x.load(std::memory_order_seq_cst));
    if(y.load(std::memory_order_seq_cst))
        ++z;
}

void read_y_then_x(void)
{
    while(!y.load(std::memory_order_seq_cst));
    if(x.load(std::memory_order_seq_cst))
        ++z;
}

int main(void)
{
    x = false;
    y = false;
    z = 0;

    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);

    a.join();
    b.join();
    c.join();
    d.join();

    assert(z.load() != 0);

    return 0;
}
