#include <memory>
#include <mutex>

struct some_resoure
{
    void do_something(void)
    {}
};

std::shared_ptr<some_resoure> resource_ptr;
std::mutex resource_mutex;

void foo(void)
{
    std::unique_lock<std::mutex> lk(resource_mutex);
    if(!resource_ptr)
    {
        resource_ptr.reset(new some_resoure);
    }
    lk.unlock();

    resource_ptr->do_something();
}

int main(void)
{
    foo();
    return 0;
}
