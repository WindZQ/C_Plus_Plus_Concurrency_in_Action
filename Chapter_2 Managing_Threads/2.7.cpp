#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

void f(void)
{
    std::vector<std::thread> threads;
    for(unsigned i = 0; i < 20; ++i)
    {
        threads.push_back(std::thread(do_work, i));
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main(void)
{
    f();
    return 0;
}
